//
//  matrix_parser.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__matrix_parser__
#define __cornerstoneVisualizationService__matrix_parser__

// headers from this project
// headers from other projects
// headers from vtk
#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>

// headers from boost
// headers from stdlib
#include <string>

// forward declarations


namespace image_data_service {
    
    namespace matrix_parser {
        
        vtkSmartPointer<vtkMatrix4x4> from_string(const std::string& str);
    }
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__matrix_parser__) */

