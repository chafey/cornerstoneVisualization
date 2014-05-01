//
//  volume_render_params.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__volume_render_params__
#define __cornerstoneVisualizationService__volume_render_params__

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
    
    struct volume_render_params
    {
        volume_render_params();
        
        std::string volumeId;
        
        // Rendering Parameters
        std::string matrix;
        int blend_mode; // 0 = composite, 1 = mip, 2 = minip, 3 = additive
        std::string transfer_function_name;
        int window_width;
        int window_level;
        int projection_type; //0 = perspective, 1 = parallel
        
        // Render Performance / Quality related
        double desired_update_rate;
        int viewport_width;
        int viewport_height;
        int interpolation_type; // 0 = nearest, 1 = linear
        
        // Resulting image properties
        int image_type; // 1 = jpeg, 0 = png
        int jpeg_quality; // 0 = lowest quality, 100 = highest quality
        int jpeg_progressive; // 1 = progressive, 0 = not progressive
        int png_compression_level; // 0 = no compression, 9 = best compression / smallest size
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__volume_render_params__) */

