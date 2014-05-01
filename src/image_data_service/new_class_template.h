//
//  new_class_template.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__new_class_template__
#define __cornerstoneVisualizationService__new_class_template__

// headers from this project
// headers from other projects
// headers from vtk
#include <vtkSmartPointer.h>
// headers from boost
#include <boost/noncopyable.hpp>
// headers from stdlib
#include <string>

// forward declarations


namespace image_data_service {
    
    class new_class_template : boost::noncopyable
    {
    public:
        explicit new_class_template();
        
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__new_class_template__) */

