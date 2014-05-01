#include "json_reply.h"
// include headers from this project
#include "json_property_tree.h"

// include headers from other projects
#include "../http_server/reply.hpp"

// include vtk headers
// include boost headers
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
// include stdlib headers



namespace image_data_service {
    
    void json_reply::write(http::server::reply& reply, const std::string& jsonString)
    {
        reply.status = http::server::reply::ok;
        reply.content = jsonString;
        reply.headers.resize(2);
        reply.headers[0].name = "Content-Length";
        reply.headers[0].value = boost::lexical_cast<std::string>(reply.content.size());
        reply.headers[1].name = "Content-Type";
        reply.headers[1].value = "text/html";
    }

    void json_reply::write(http::server::reply& reply, const boost::property_tree::ptree& propertyTree, bool fix_json_types)
    {
        // convert to json string
        std::ostringstream buf;
        boost::property_tree::write_json (buf, propertyTree, false);
        std::string json = buf.str();
        
        if(fix_json_types) {
            json = json_property_tree::fix_json_types(json);
        }
        
        json_reply::write(reply, json);
    }

    
} // namespace image_data_service

