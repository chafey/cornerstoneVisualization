#include "stdafx.h"
#include "volume_render_params.h"
// include headers from this project
// include headers from other projects
// include vtk headers
// include boost headers
// include stdlib headers

namespace image_data_service {
    
    
    volume_render_params::volume_render_params()
    {
        volumeId = "volume1";
        
        matrix = "1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1";
        blend_mode = 0; // composite
        transfer_function_name = "high contrast";
        window_width = 270;
        window_level = 340;
        projection_type = 1; // parallel
        render_engine = 2; // software

        desired_update_rate = 2.0; // good image quality
        viewport_height =512;
        viewport_width = 512;
        interpolation_type = 1; // linear
        
        image_type = 1; // jpeg
        jpeg_quality = 30; // low image quality
        png_compression_level = 5; // medium compression level
        jpeg_progressive = 0; // not progressive
    }
    
    
} // namespace image_data_service

