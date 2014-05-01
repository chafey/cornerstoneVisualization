//
//  volume_loader_handler.h
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/24/14.
//
//

#ifndef __cornerstoneVisualizationService__volume_loader_handler__
#define __cornerstoneVisualizationService__volume_loader_handler__

#include "../http_server/request_handler.hpp"

namespace image_data_service {
    
    // request handler for loading volumes
    class volume_loader_handler : public http::server::request_handler
    {
    public:
        
        /// Handle a request and produce a reply.
        virtual void handle_request(const http::server::request& req, http::server::reply& rep);
        
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__volume_loader_handler__) */
