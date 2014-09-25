#include "stdafx.h"
#include "string_helper.h"
// include headers from this project
// include headers from other projects
// include vtk headers
// include boost headers
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
// include stdlib headers

namespace image_data_service {
    
    void string_helper::extract_doubles(const std::string& source, std::vector<double>& doubles)
    {
        doubles.clear();
        std::vector<std::string> strings;
        boost::split(strings, source, boost::is_any_of(","));
        std::transform(strings.begin(), strings.end(),
                       std::back_inserter(doubles),
                       boost::lexical_cast<double, std::string>);
    }


    
} // namespace image_data_service

