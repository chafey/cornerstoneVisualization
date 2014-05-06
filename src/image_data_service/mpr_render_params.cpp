#include "mpr_render_params.h"
// include headers from this project
#include "string_helper.h"
// include headers from other projects
// include vtk headers
// include boost headers
// include stdlib headers
#include <limits.h>

namespace image_data_service {
    
    
    mpr_render_params::mpr_render_params()
    {
        volumeId = "volume1";
        
        static const double adc[] = {1,0,0,0,1,0,0,0,1}; // identity/axial
        axes_direction_cosines = std::vector<double>(adc, adc + 9);;
        static const double rao[] = {0,0,0}; // center of volume
        reslice_axes_origin = std::vector<double>(rao, rao +3);
        blend_mode = 2; // mean
        window_width = 400;
        window_level = 40;
        slab_thickness = 10.0;
        slab_resolution = 1.0;
        
        viewport_height =512;
        viewport_width = 512;
        interpolation_mode = 1; // linear
        background_level = -1000; // Air in CT
        
        image_type = 0; // png
        jpeg_quality = 30; // low image quality
        png_compression_level = 1; // low compression level
        jpeg_progressive = 0; // not progressive
    }
    
    
} // namespace image_data_service

