//
//  jpeg_reply.cpp
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/25/14.
//
//

#include "jpeg_reply.h"

#include "../http_server/mime_types.hpp"
#include "../http_server/reply.hpp"

#include <vtkSmartPointer.h>
#include <vtkWindowToImageFilter.h>
#include <vtkJPEGWriter.h>
#include <vtkUnsignedCharArray.h>

#include <string>
#include <boost/lexical_cast.hpp>


namespace image_data_service {
    

    void jpeg_reply::write(http::server::reply& reply, vtkWindowToImageFilter& windowToImageFilter, unsigned int quality, unsigned int progressive)
    {
        // hook up an in memory jpeg writer to the window image filter
        vtkSmartPointer<vtkJPEGWriter> writer = vtkSmartPointer<vtkJPEGWriter>::New();
        writer->WriteToMemoryOn();
        writer->SetInputConnection(windowToImageFilter.GetOutputPort());
        writer->SetQuality(quality);
        writer->SetProgressive(progressive);
        writer->Write();
        
        // Get the jpeg data stream 
        vtkSmartPointer<vtkUnsignedCharArray> dataPtr = writer->GetResult();
        dataPtr->Squeeze();

        // Return the reply
        reply.status = http::server::reply::ok;
        reply.content = std::string((char*)dataPtr->GetPointer(0), dataPtr->GetSize());
        reply.headers.resize(3);
        reply.headers[0].name = "Content-Length";
        reply.headers[0].value = boost::lexical_cast<std::string>(reply.content.size());
        reply.headers[1].name = "Content-Type";
        reply.headers[1].value = http::server::mime_types::extension_to_type("jpg");
        reply.headers[2].name = "Access-Control-Allow-Origin";
        reply.headers[2].value = "*";
    }
        
} // namespace image_data_service
