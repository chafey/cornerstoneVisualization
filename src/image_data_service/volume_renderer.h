//
//  volume_renderer.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__volume_renderer__
#define __cornerstoneVisualizationService__volume_renderer__

// headers from this project
// headers from other projects
// headers from vtk
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkVolumeProperty.h>
#include <vtkVolumeMapper.h>
#include <vtkVolume.h>
#include <vtkCamera.h>
#include <vtkImageData.h>
#include <vtkSmartVolumeMapper.h>

// headers from boost
#include <boost/noncopyable.hpp>
// headers from stdlib

// forward declarations

namespace image_data_service {
    
    struct volume_renderer
    {
        volume_renderer(vtkSmartPointer<vtkImageData> imageData, int max_width, int max_height);
        
        vtkSmartPointer<vtkRenderer> renderer;
        
        vtkSmartPointer<vtkRenderWindow> render_window;
        
        vtkSmartPointer<vtkVolumeProperty> volume_property;
        
        vtkSmartPointer<vtkSmartVolumeMapper> volume_mapper;
        
        vtkSmartPointer<vtkVolume> volume;
        
        vtkSmartPointer<vtkCamera> camera;
    
        // the maximum width this volume_renderer can render
        int max_width;
        
        // the maximum height this volume_renderer can render
        int max_height;
        
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__volume_renderer__) */

