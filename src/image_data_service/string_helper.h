//
//  string_helper.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__string_helper__
#define __cornerstoneVisualizationService__string_helper__

// headers from this project
// headers from other projects
// headers from vtk
// headers from boost
// headers from stdlib
#include <string>
#include <vector>

// forward declarations


namespace image_data_service {
    
    namespace string_helper {
        void extract_doubles(const std::string& source, std::vector<double>& doubles);
    }
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__string_helper__) */

