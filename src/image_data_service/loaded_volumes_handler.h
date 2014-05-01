//
//  volume_handler.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__volume_handler__
#define __cornerstoneVisualizationService__volume_handler__

// headers from this project
// headers from other projects
#include "../http_server/request_handler.hpp"
// headers from vtk
#include <vtkSmartPointer.h>
// headers from boost
// headers from stdlib
#include <string>

// forward declarations


namespace image_data_service {
    
    class loaded_volumes_handler : public http::server::request_handler

    {
    public:
        explicit loaded_volumes_handler();
        
        /// Handle a request and produce a reply.
        virtual void handle_request(const http::server::request& req, http::server::reply& rep);

    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__volume_handler__) */

