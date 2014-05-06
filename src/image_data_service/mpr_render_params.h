//
//  mpr_render_params.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__mpr_render_params__
#define __cornerstoneVisualizationService__mpr_render_params__

// headers from this project
// headers from other projects
// headers from vtk
// headers from boost
// headers from stdlib
#include <string>
#include <vector>
// forward declarations


namespace image_data_service {
    
    struct mpr_render_params
    {
        mpr_render_params();
        
        std::string volumeId;
        
        // Rendering Parameters
        std::vector<double> axes_direction_cosines;
        std::vector<double> reslice_axes_origin;
        int blend_mode; // 0 = min, 1 = max, 2 = mean
        int window_width; // only for png and jpeg image types
        int window_level; // only for png and jpeg image types
        double slab_thickness; // slab thickness
        double slab_resolution; // slab resolution SlabResolution=min(spacing[0], spacing[1], spacing[2])

        // Render Performance / Quality related
        int viewport_width;
        int viewport_height;
        int interpolation_mode; // 0 = nearest, 1 = linear, 2 = cubic
        double background_level; // the gray value to use for the background/border pixels
        
        // Resulting image properties
        int image_type; // 0=png, 1=jpeg, 2=16 bit
        int jpeg_quality; // 0 = lowest quality, 100 = highest quality
        int jpeg_progressive; // 1 = progressive, 0 = not progressive
        int png_compression_level; // 0 = no compression, 9 = best compression / smallest size
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__mpr_render_params__) */

