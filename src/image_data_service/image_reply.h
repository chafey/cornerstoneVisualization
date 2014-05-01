//
//  image_reply.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__image_reply__
#define __cornerstoneVisualizationService__image_reply__

// headers from this project
// headers from other projects
// headers from vtk
// headers from boost
// headers from stdlib

// forward declarations

class vtkRenderWindow;

namespace http {
    namespace server {
        struct reply;
    }
}

namespace image_data_service {
    
    namespace image_reply
    {
        void write(http::server::reply& rep, vtkRenderWindow& renderWindow, int image_type, int jpeg_quality, int jpeg_progressive, int png_compression_level);
    }
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__image_reply__) */

