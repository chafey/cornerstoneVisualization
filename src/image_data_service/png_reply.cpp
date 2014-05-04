//
//  png_reply.cpp
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/25/14.
//
//

#include "png_reply.h"

#include "../http_server/mime_types.hpp"
#include "../http_server/reply.hpp"

#include <vtkSmartPointer.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#include <vtkUnsignedCharArray.h>

#include <string>
#include <boost/lexical_cast.hpp>


namespace image_data_service {
    
    void png_reply::write(http::server::reply& reply, vtkWindowToImageFilter& windowToImageFilter, int compressionLevel)
    {
        // hook up an in memory png writer to the window image filter
        vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
        writer->WriteToMemoryOn();
        writer->SetInputConnection(windowToImageFilter.GetOutputPort());
        writer->SetCompressionLevel(compressionLevel);
        writer->Write();
        
        // Get the png data stream
        vtkSmartPointer<vtkUnsignedCharArray> dataPtr = writer->GetResult();
        dataPtr->Squeeze();

        // Return the reply
        reply.status = http::server::reply::ok;
        reply.content = std::string((char*)dataPtr->GetPointer(0), dataPtr->GetSize());
        reply.headers.resize(3);
        reply.headers[0].name = "Content-Length";
        reply.headers[0].value = boost::lexical_cast<std::string>(reply.content.size());
        reply.headers[1].name = "Content-Type";
        reply.headers[1].value = http::server::mime_types::extension_to_type("png");
        reply.headers[2].name = "Access-Control-Allow-Origin";
        reply.headers[2].value = "*";
    }
    
    
} // namespace image_data_service
