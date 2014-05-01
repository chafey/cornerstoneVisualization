//
//  json_reply.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__json_reply__
#define __cornerstoneVisualizationService__json_reply__

// headers from this project
// headers from other projects
// headers from vtk
// headers from boost
#include <boost/property_tree/ptree.hpp>
// headers from stdlib
#include <string>

// forward declarations

namespace http {
    namespace server {
        struct reply;
    }
}

namespace image_data_service {
    namespace json_reply {
        
        void write(http::server::reply& reply, const std::string& jsonString);
        void write(http::server::reply& reply, const boost::property_tree::ptree& propertyTree, bool fix_json_types = false);

    }
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__json_reply__) */

