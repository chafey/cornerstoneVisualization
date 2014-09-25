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

#include "../http_server/mime_types.hpp"
#include "../http_server/reply.hpp"
#include "../http_server/request.hpp"
#include "../http_server/url.hpp"
#include "../http_server/hef_uri_syntax.hpp"
#include "../http_server/query_parser.hpp"

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <fstream>
#include <sstream>
#include <string>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;


namespace image_data_service {
    
    void volume_loader_handler::handle_request(const http::server::request& req, http::server::reply& rep)
    {
        // parse out url parameters
        hef::HfURISyntax uri(req.uri);
        std::string query = uri.getQuery();
        std::map<std::string, std::string> parameters = http::server::query_parser::parse(query);
        
        // get the volume
        std::string volumeId = parameters["volumeId"];
        volume& vol = volume_manager::instance().get(volumeId);
        
        ptree pt = volume_to_property_tree::from(vol);
        
        json_reply::write(rep, pt, true);
    }
        
} // namespace image_data_service
