#include "stdafx.h"

#include "json_property_tree.h"
// include headers from this project
// include headers from other projects
// include vtk headers
// include boost headers
// include stdlib headers

namespace image_data_service {
    
    namespace json_property_tree {
        std::string fix_json_types(std::string jsonString)
        {
            boost::regex exp("\"(null|true|false|[0-9]+(\\.[0-9]+)?)\"");
            std::string rv = boost::regex_replace(jsonString, exp, "$1");
            return rv;
        }
        
    }
    
    
    
} // namespace image_data_service

