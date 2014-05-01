//
//  volume_to_property_tree.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__volume_to_property_tree__
#define __cornerstoneVisualizationService__volume_to_property_tree__

// headers from this project
// headers from other projects
// headers from vtk
// headers from boost
#include <boost/property_tree/ptree.hpp>
// headers from stdlib

// forward declarations


namespace image_data_service {
    
    class volume;
    
    namespace volume_to_property_tree {
        
        boost::property_tree::ptree from(volume& vol);
        
    }
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__volume_to_property_tree__) */

