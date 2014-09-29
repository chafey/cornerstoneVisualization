#include "stdafx.h"
//
//  status_request_handler.cpp
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/24/14.
//
//

#include "volume_loader_handler.h"
#include "json_reply.h"
#include "volume_loader.h"
#include "volume_cache.h"
#include "volume_manager.h"
#include "volume_to_property_tree.h"
#include "json_property_tree.h"
#include "volume.h"

#include "../http_server/mime_types.hpp"
#include "../http_server/reply.hpp"
#include "../http_server/request.hpp"
#include "../http_server/url.hpp"
#include "../http_server/hef_uri_syntax.hpp"
#include "../http_server/query_parser.hpp"

/*
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/network/protocol/http/client.hpp>

#include <fstream>
#include <sstream>
#include <string>
*/
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

/*

{
"dimensions" : {
"x" : 512,
"y" : 512,
"z" : 6
},
"spacing" : {
"x" : 0.675781,
"y" : 0.675781,
"z" : 2.5
},
"imageUris" : [
"http://10.211.55.3:8042/instances/3007b351-b0d3eb66-906b11b4-544ef66b-32612967/attachments/dicom/compressed-data",
"http://10.211.55.3:8042/instances/bdaec587-9b657f21-8924b457-33c17867-c820d828/attachments/dicom/compressed-data",
"http://10.211.55.3:8042/instances/0acc5cea-46f60250-1f0a1c18-2ca93ca9-7b613826/attachments/dicom/compressed-data",
"http://10.211.55.3:8042/instances/2a9955de-965cb941-64bf1118-8b844cc0-35a77c3b/attachments/dicom/compressed-data",
"http://10.211.55.3:8042/instances/ac82467c-ff5a52a8-00377dec-fec8a382-c7a2052a/attachments/dicom/compressed-data",
"http://10.211.55.3:8042/instances/a28c110d-109e726e-dd6cbcc6-6529095f-1e973a4f/attachments/dicom/compressed-data"
],
"dataType" : 4,
"volumeId" : "volume3"
}

*/

/*
dataTypes:
24 #define VTK_VOID            0
25 #define VTK_BIT             1
26 #define VTK_CHAR            2
27 #define VTK_SIGNED_CHAR    15
28 #define VTK_UNSIGNED_CHAR   3
29 #define VTK_SHORT           4
30 #define VTK_UNSIGNED_SHORT  5
31 #define VTK_INT             6
32 #define VTK_UNSIGNED_INT    7
33 #define VTK_LONG            8
34 #define VTK_UNSIGNED_LONG   9
35 #define VTK_FLOAT          10
36 #define VTK_DOUBLE         11
37 #define VTK_ID_TYPE        12

*/

using boost::asio::ip::tcp;

namespace image_data_service {
    
  bool is_valid(ptree& pt) {
    return true;
  }

  int pixel_size(int dataType)
  {
    if (dataType == 4 || dataType == 5) {
      return 2;
    }
    if (dataType == 2 || dataType == 15) {
      return 1;
    }
    return 0;
  }

  bool build_volume(ptree pt, vtkSmartPointer<vtkImageData>& imageData)
  {
    int dimX= pt.get<int>(ptree::path_type("dimensions.x"));
    int dimY = pt.get<int>(ptree::path_type("dimensions.y"));
    int dimZ = pt.get<int>(ptree::path_type("dimensions.z"));
    float spacingX = pt.get<float>(ptree::path_type("spacing.x"));
    float spacingY = pt.get<float>(ptree::path_type("spacing.y"));
    float spacingZ = pt.get<float>(ptree::path_type("spacing.z"));
    int dataType = pt.get<int>(ptree::path_type("dataType"));
    int pixelSize = pixel_size(dataType);
    int imageDataLength = dimX * dimY * pixelSize;

    if (pixelSize == 0) {
      return false;
    }
    if (dimZ != pt.get_child("imageUris").size())
    {
      return false;
    }

    imageData = vtkImageData::New();
    imageData->SetDimensions(dimX, dimY, dimZ);
    imageData->SetSpacing(spacingX, spacingY, spacingZ);
    imageData->AllocateScalars(dataType, 1);
    void* buffer = imageData->GetScalarPointer();

    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    // TODO: Make multiple simultaneous http requests - perhaps using asynchronously?
    BOOST_FOREACH(const ptree::value_type& child,
      pt.get_child("imageUris"))
    {
      std::string imageUri = child.second.get<std::string>("");
      boost::network::http::client client;
      boost::network::http::client::request request(imageUri);
      request << boost::network::header("Connection", "close");
      boost::network::http::client::response response = client.get(request);
      std::string bodyz = body(response);
      //std::cout << "read " << bodyz.size() << " bytes" << std::endl;
      const char* pPixelData = (bodyz.c_str() + bodyz.size() - imageDataLength);

      // DICOM stores the upper left pixel as the first pixel in an
      // image. VTK stores the lower left pixel as the first pixel in
      // an image.  Need to flip the data.
      vtkIdType rowLength;
      rowLength = dimX * pixelSize;
      unsigned char *b = (unsigned char *)buffer;
      unsigned char *iData = (unsigned char *)pPixelData;
      iData += (imageDataLength - rowLength); // beginning of last row
      for (int i = 0; i < dimY; ++i)
      {
        memcpy(b, iData, rowLength);
        b += rowLength;
        iData -= rowLength;
      }
      buffer = ((char*)buffer) + imageDataLength;

    }
    
    return true;
  }


  void volume_loader_handler::handle_request(const http::server::request& req, http::server::reply& rep)
  {
    // Return error if they use another method besides POST
    if (req.method != "POST")
    {
      rep = http::server::reply::stock_reply(http::server::reply::method_not_allowed);
      return;
    }

    // Parse the JSON
    ptree pt;
    std::istringstream input(req.body);
    read_json(input, pt);

    // Validate JSON and return error if it is incorrect
    if (!is_valid(pt)) {
      rep = http::server::reply::stock_reply(http::server::reply::bad_request);
      return;
    }

    // If client requests using cached volume, do nothing if this volume is in cache
    std::string volumeId = pt.get<std::string>(ptree::path_type("volumeId"));
    volume_cache volumeCache(volume_manager::instance().volume_root());
    bool useCachedVolume = pt.get<bool>(ptree::path_type("useCachedVolume"));
    if (useCachedVolume) {
      if (volume_manager::instance().is_cached(volumeId))
      {
        // volume is cached, go ahead and load it (if it isn't already loaded)
        volume_manager::instance().get(volumeId);
        return;
      }
    }

    // Volume not in cache, build it 
    vtkSmartPointer<vtkImageData> imageData;
    if (!build_volume(pt, imageData))
    {
      rep = http::server::reply::stock_reply(http::server::reply::bad_request);
      return;
    }

    // Add the built volume to the volume manager
    // TODO: what happens if volume is already loaded?
    volume_manager::instance().put(volumeId, new volume(imageData));

    // if client allows caching of the volume, cache it
    bool cacheVolume = pt.get<bool>(ptree::path_type("cacheVolume"));
    if (cacheVolume) {
      volumeCache.write(volumeId, imageData);
    }

    // Return response 
    ptree response;

    json_reply::write(rep, response, true);
  }
        
} // namespace image_data_service
