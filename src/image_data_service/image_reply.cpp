#include "image_reply.h"
// include headers from this project
#include "png_reply.h"
#include "jpeg_reply.h"
// include headers from other projects
// include vtk headers
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkWindowToImageFilter.h>
// include boost headers
// include stdlib headers

namespace image_data_service {
    
    
    void image_reply::write(http::server::reply& rep, vtkRenderWindow& renderWindow, int image_type, int jpeg_quality, int jpeg_progressive, int png_compression_level)
    {
        // render the image
        vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
        windowToImageFilter->SetInput(&renderWindow);
        windowToImageFilter->Update();
        
        // return it as a jpeg or png
        if(image_type == 1) {
            jpeg_reply::write(rep, *windowToImageFilter, jpeg_quality, jpeg_progressive);
        } else {
            png_reply::write(rep, *windowToImageFilter, png_compression_level);
        }
    }

    
} // namespace image_data_service

