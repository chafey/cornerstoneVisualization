//
//  jpeg_reply.h
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/25/14.
//
//

#ifndef __cornerstoneVisualizationService__jpeg_reply__
#define __cornerstoneVisualizationService__jpeg_reply__

class vtkWindowToImageFilter;

namespace http {
    namespace server {
        struct reply;
    }
}

namespace image_data_service {
    namespace jpeg_reply {

        // writes a jpeg image as a reply to an http request with the specified quality and progressive on/off
        void write(http::server::reply& reply, vtkWindowToImageFilter& windowToImageFilter, unsigned int quality = 30, unsigned int progressive = 0);
    
    } // namespace jpeg_reply
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__jpeg_reply__) */
