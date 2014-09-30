#include "stdafx.h"
#include "mpr_handler.h"
// include headers from this project
#include "mpr_render_params_parser.h"
#include "volume_manager.h"
#include "image_reply.h"
#include "render_event.h"

// include headers from other projects
#include "../http_server/request.hpp"

// include vtk headers
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkImageSlabReslice.h>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkImageMapper3D.h>

// include boost headers
#include <boost/timer/timer.hpp>
// include stdlib headers

namespace image_data_service {
    
    void mpr_handler::handle_request(const http::server::request& req, http::server::reply& rep)
    {
        render_event item(req.uri);
        
        // parse the render parameters
        mpr_render_params renderParams = mpr_render_params_parser::from_uri(req.uri);
        
        // get the volume and its mpr_renderer
        volume& volume = volume_manager::instance().get(renderParams.volumeId);
        boost::shared_ptr<struct mpr_renderer> renderer = volume.mpr_renderer();
    
        // setup render parameters
        renderer->image_slab_reslice->SetInterpolationMode(renderParams.interpolation_mode);
        renderer->image_slab_reslice->SetSlabThickness(renderParams.slab_thickness);
        //imageReslice->SetSlabResolution(renderParams.slab_resolution);
        renderer->image_slab_reslice->SetBlendMode(renderParams.blend_mode);
        renderer->image_slab_reslice->SetResliceAxesOrigin(renderParams.reslice_axes_origin[0],
                                           renderParams.reslice_axes_origin[1],
                                           renderParams.reslice_axes_origin[2]);
        renderer->image_slab_reslice->SetResliceAxesDirectionCosines(renderParams.axes_direction_cosines[0],
                                                     renderParams.axes_direction_cosines[1],
                                                     renderParams.axes_direction_cosines[2],
                                                     renderParams.axes_direction_cosines[3],
                                                     renderParams.axes_direction_cosines[4],
                                                     renderParams.axes_direction_cosines[5],
                                                     renderParams.axes_direction_cosines[6],
                                                     renderParams.axes_direction_cosines[7],
                                                     renderParams.axes_direction_cosines[8]);
        renderer->image_slab_reslice->SetBackgroundLevel(renderParams.background_level);

        // ww/wc
        //int min = renderParams.window_level - renderParams.window_width / 2;
        //int max = min + renderParams.window_width;
        //renderer->lookup_table->SetRange(min, max); // image intensity range
        //renderer->image_map_to_colors->SetLevel(renderParamers.window_level);
        renderer->image_shift_scale->SetShift(0.5*renderParams.window_width - renderParams.window_level);
        renderer->image_shift_scale->SetScale(255.0 / renderParams.window_width);

        // render the image
        renderer->render_window->SetSize(renderParams.viewport_width, renderParams.viewport_height);
        renderer->render_window->Render();
      
        // return the image
        image_reply::write(rep, *renderer->render_window, renderParams.image_type, renderParams.jpeg_quality, renderParams.jpeg_progressive, renderParams.png_compression_level);
    }
    
    
} // namespace image_data_service

