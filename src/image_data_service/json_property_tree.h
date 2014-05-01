//
//  json_property_tree.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__json_property_tree__
#define __cornerstoneVisualizationService__json_property_tree__

// headers from this project
// headers from other projects
// headers from vtk
// headers from boost
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
// headers from stdlib
#include <string>

// forward declarations


namespace image_data_service {

    // helper functions to workaround boost property tree's lack of support for non string types
    namespace json_property_tree {
        
        // wraps non string types with quotes to workaround write_json's lack of support for
        // non string types.  You can use fix_json_types() below to remove these escape characters
        template<typename T>
            void put(boost::property_tree::ptree& pt, const char* name, T value)
        {
            std::string str = boost::lexical_cast<std::string>(value);
            pt.put(name, str);
        }
        
        // This function uses a regex to remove quotes around json values that are not strings.
        // NOTE: This is workaround for boost property tree's lack of support for anything but string json types.
        // NOTE: Beware of using this if you need to pass string values that look like any of the strings in the regular expression!
        // Based on: http://stackoverflow.com/questions/13464383/boost-property-write-json-incorrect-behaviour
        std::string fix_json_types(std::string jsonString);

    }
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__json_property_tree__) */

