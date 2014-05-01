//
//  png_reply.h
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/25/14.
//
//

#ifndef __cornerstoneVisualizationService__png_reply__
#define __cornerstoneVisualizationService__png_reply__

class vtkWindowToImageFilter;

namespace http {
    namespace server {
        struct reply;
    }
}

namespace image_data_service {
    
    namespace png_reply {
        
       void write(http::server::reply& reply, vtkWindowToImageFilter& windowToImageFilter, int compressionLevel = 5);
        
    } // namespace png_reply
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__jpeg_reply__) */
