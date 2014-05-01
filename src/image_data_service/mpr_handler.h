//
//  mpr_handler.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__mpr_handler__
#define __cornerstoneVisualizationService__mpr_handler__

// headers from this project
// headers from other projects
#include "../http_server/request_handler.hpp"
// headers from boost
// headers from stdlib

// forward declarations

namespace image_data_service {
    
    class mpr_handler : public http::server::request_handler
    {
    public:
       
        /// Handle a request and produce a reply.
        virtual void handle_request(const http::server::request& req, http::server::reply& rep);
        
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__mpr_handler__) */

