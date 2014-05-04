//
//  status_request_handler.cpp
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/24/14.
//
//

#include "volume_renderer_handler.h"

// include headers from this project
#include "volume_manager.h"
#include "render_window_manager.h"
#include "volume_loader.h"
#include "volume_cache.h"
#include "transfer_function_library.h"
#include "transfer_function.h"
#include "volume_render_params.h"
#include "volume_render_params_parser.h"
#include "image_reply.h"
#include "matrix_parser.h"
#include "render_event.h"
#include "log.h"

// include headers from other projects
#include "../http_server/request.hpp"

// include vtk headers
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkVolumeProperty.h>
#include <vtkRendererCollection.h>
#include <vtkCamera.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkTransform.h>

// include boost headers
#include <boost/timer/timer.hpp>
#include <algorithm>    // std::max


namespace image_data_service {
    
    void volume_renderer_handler::handle_request(const http::server::request& req, http::server::reply& rep)
    {
        render_event item(req.uri);
        
        volume_render_params renderParams = volume_render_params_parser::from_uri(req.uri);
        
        volume& volume = volume_manager::instance().get(renderParams.volumeId);
        
        boost::shared_ptr<struct volume_renderer> volumeRenderer = volume.volume_renderer(renderParams.viewport_width, renderParams.viewport_height);
        
        // Update the render window parameters
        volumeRenderer->render_window->SetSize(renderParams.viewport_width, renderParams.viewport_height);
        volumeRenderer->render_window->SetDesiredUpdateRate(renderParams.desired_update_rate);
        
        // update the volume property parameters
        const boost::shared_ptr<transfer_function> transferFunction = transfer_function_library::instance().get(renderParams.transfer_function_name);
        volumeRenderer->volume_property->SetScalarOpacity(transferFunction->opacity());
        volumeRenderer->volume_property->SetColor(transferFunction->color());
        volumeRenderer->volume_property->SetInterpolationType(renderParams.interpolation_type);
        
        // Update the volume mapper parameters
        volumeRenderer->volume_mapper->SetBlendMode(renderParams.blend_mode);
        volumeRenderer->volume_mapper->SetRequestedRenderMode(renderParams.render_engine);
        // TODO: Implement window/level.
        // NOTE: This code doesn't "look right" so it is commented out for now
        /*
         int maxValue = 1000;
         int minValue = -1024;
         int range = maxValue - minValue;
         double wl = ((double)renderParams.window_level - (double)minValue) / (double)range;
         mapper->SetFinalColorLevel(wl);
         double ww = ((double)renderParams.window_width / (double)range);
         mapper->SetFinalColorWindow(ww);
         */
        
        // Create a new camera and sets its matrix
        vtkSmartPointer<vtkMatrix4x4> mm = matrix_parser::from_string(renderParams.matrix);
        vtkSmartPointer<vtkCamera> camera = volumeRenderer->renderer->MakeCamera();
        camera->DeepCopy(volumeRenderer->camera);
      
		vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
		transform->SetMatrix(mm);
		transform->Inverse();
		camera->ApplyTransform(transform);
		
		// Set the clipping planes so the volume doesn't get clipped
		double clipNear = camera->GetDistance() - volume.max_radius;
		double clipFar = clipNear + (volume.max_radius * 2.0);
		if(clipNear < 1.0) {
			clipNear = 1.0;
		}
		camera->SetClippingRange(clipNear, clipFar);
		
        // update the volume renderer parameters
        volumeRenderer->renderer->SetActiveCamera(camera);
        
        // render an image and return it as the response
        volumeRenderer->render_window->Render();
        image_reply::write(rep, *volumeRenderer->render_window, renderParams.image_type, renderParams.jpeg_quality, renderParams.jpeg_progressive, renderParams.png_compression_level);
    }
    
    
    
    
} // namespace image_data_service
