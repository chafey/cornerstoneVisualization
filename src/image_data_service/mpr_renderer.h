//
//  mpr_renderer.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__mpr_renderer__
#define __cornerstoneVisualizationService__mpr_renderer__

// headers from this project
// headers from other projects
// headers from vtk
#include <vtkSmartPointer.h>
#include <vtkImageSlabReslice.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>
#include <vtkImageActor.h>
// headers from boost
#include <boost/noncopyable.hpp>
// headers from stdlib
#include <string>

// forward declarations


namespace image_data_service {
    
    struct mpr_renderer
    {
        explicit mpr_renderer(vtkSmartPointer<vtkImageData> imageData);
        
        vtkSmartPointer<vtkImageSlabReslice> image_slab_reslice;

        vtkSmartPointer<vtkRenderWindow> render_window;
        
        vtkSmartPointer<vtkRenderer> renderer;
        
        vtkSmartPointer<vtkLookupTable> lookup_table;
        
        vtkSmartPointer<vtkImageMapToColors> image_map_to_colors;
        
        vtkSmartPointer<vtkImageActor> image_actor;
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__mpr_renderer__) */

