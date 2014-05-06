#include "loaded_volumes_handler.h"
// include headers from this project
#include "volume_manager.h"
#include "volume.h"
#include "json_reply.h"
#include "volume_to_property_tree.h"
#include "json_property_tree.h"

// include headers from other projects
#include "../http_server/hef_uri_syntax.hpp"
#include "../http_server/query_parser.hpp"
#include "../http_server/mime_types.hpp"
#include "../http_server/reply.hpp"
#include "../http_server/request.hpp"
#include "../http_server/url.hpp"

// include vtk headers
// include boost headers
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
// include stdlib headers

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

namespace image_data_service {
    
    
    loaded_volumes_handler::loaded_volumes_handler()
    {
    }
    
    void loaded_volumes_handler::handle_request(const http::server::request& req, http::server::reply& rep)
    {
        // get the loaded volumes
        std::vector<volume*> volumes = volume_manager::instance().loaded_volumes();
        
        // build the property tree
        ptree pt;
        ptree arrayChild;

        for(int i=0; i < volumes.size(); i++) {
            volume* vol = volumes[i];
            ptree arrayElement;
            arrayElement = volume_to_property_tree::from(*vol);
            arrayChild.push_back(std::make_pair("",arrayElement));
        }
        pt.put_child(ptree::path_type("volumes"), arrayChild);
        
        json_reply::write(rep, pt, true);
    }

    
} // namespace image_data_service

