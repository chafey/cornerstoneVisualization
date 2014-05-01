//
//  status_request_handler.h
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/24/14.
//
//

#ifndef __cornerstoneVisualizationService__status_request_handler__
#define __cornerstoneVisualizationService__status_request_handler__

#include "../http_server/request_handler.hpp"

namespace http {
    namespace server {
        struct request;
        struct reply;
        class request_handler;
    }
}

namespace image_data_service {
    
    /// The common handler for all incoming requests.
    class status_request_handler : public http::server::request_handler
    {
    public:
        
        /// Handle a request and produce a reply.
        virtual void handle_request(const http::server::request& req, http::server::reply& rep);
        
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__status_request_handler__) */
