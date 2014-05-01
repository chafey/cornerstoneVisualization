//
//  volume_render_params_parser.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__volume_render_params_parser__
#define __cornerstoneVisualizationService__volume_render_params_parser__

// headers from this project
#include "volume_render_params.h"
// headers from other projects
// headers from vtk
// headers from boost
// headers from stdlib
#include <string>

// forward declarations


namespace image_data_service {
    
    namespace volume_render_params_parser {
        
        volume_render_params from_uri(const std::string& uriString);
        
    }
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__volume_render_params_parser__) */

