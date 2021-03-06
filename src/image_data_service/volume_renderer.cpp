#include "stdafx.h"
#include "volume_renderer.h"
// include headers from this project
#include "log.h"
// include headers from other projects
// include vtk headers
#include <vtkSmartVolumeMapper.h>
// include boost headers
// include stdlib headers

namespace image_data_service {
    
    
    static vtkSmartPointer<vtkSmartVolumeMapper> create_volume_mapper()
    {
        vtkSmartPointer<vtkSmartVolumeMapper> mapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
        mapper->SetRequestedRenderMode(vtkSmartVolumeMapper::RayCastRenderMode);
        //mapper->SetRequestedRenderMode(vtkSmartVolumeMapper::TextureRenderMode );
        //mapper->SetRequestedRenderMode(vtkSmartVolumeMapper::GPURenderMode  );
        //mapper->SetRequestedRenderMode(vtkSmartVolumeMapper::RayCastAndTextureRenderMode  );
        return mapper;
    }
    
    volume_renderer::volume_renderer(vtkSmartPointer<vtkImageData> imageData, int maxWidth, int maxHeight)
    {
		LINFO << "volume_renderer()";
        max_width = maxWidth;
        max_height = maxHeight;
        
        renderer = vtkSmartPointer<vtkRenderer>::New();
        renderer->LightFollowCameraOn(); // not needed?

        render_window = vtkSmartPointer<vtkRenderWindow>::New();
        render_window->SetOffScreenRendering(1);
        render_window->AddRenderer(renderer);
        
        render_window->SetSize(max_width, max_height);
        
        volume_property = vtkSmartPointer<vtkVolumeProperty>::New();
        
        volume_mapper = create_volume_mapper();
        volume_mapper->SetInputData( imageData );
        volume_mapper->CroppingOff(); // this may be the default...

		volume = vtkSmartPointer<vtkVolume>::New();
        volume->SetMapper(volume_mapper);
        volume->SetProperty(volume_property);
        
        
        renderer->AddViewProp(volume);
        render_window->Render();
        
        vtkSmartPointer<vtkCamera> activeCamera = renderer->GetActiveCamera();
        renderer->SetActiveCamera(activeCamera); // not needed?
        render_window->Render(); //not needed?
        
        camera = vtkSmartPointer<vtkCamera>::New();
        camera->DeepCopy(activeCamera);
		LINFO << "volume_renderer() - done";
    }
    
    
} // namespace image_data_service

