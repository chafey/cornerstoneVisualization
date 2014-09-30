#include "stdafx.h"
#include "mpr_renderer.h"
// include headers from this project
// include headers from other projects
// include vtk headers
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>

// include boost headers
// include stdlib headers

namespace image_data_service {
    
    
    mpr_renderer::mpr_renderer(vtkSmartPointer<vtkImageData> imageData)
    {
        image_slab_reslice = vtkImageSlabReslice::New();
        image_slab_reslice->SetInputData(imageData);
        image_slab_reslice->SetOutputDimensionality(2);
        image_slab_reslice->AutoCropOutputOn();

        double range[2];
        imageData->GetScalarRange(range);


        // Create a greyscale lookup table
        lookup_table = vtkLookupTable::New();
        //lookup_table->SetRange(0.0, 1.0); // image intensity range
        lookup_table->SetRange(range[0], range[1]); // image intensity range
        lookup_table->SetHueRange(0.0, 0.0); 
        lookup_table->SetValueRange(0.0, 1.0); // from black to white
        lookup_table->SetSaturationRange(0.0, 0.0); // no color saturation
        lookup_table->SetAlphaRange(1.0, 1.0);
        lookup_table->SetRampToLinear();
        lookup_table->Build();
        
        image_shift_scale = vtkImageShiftScale::New();
        //image_shift_scale->SetShift(0.5*window - level);
        //image_shift_scale->SetScale(255.0 / window);
        image_shift_scale->ClampOverflowOn();
        image_shift_scale->SetOutputScalarTypeToUnsignedChar();
        image_shift_scale->SetInputConnection(image_slab_reslice->GetOutputPort());

        // Map the image through the lookup table
        //image_map_to_colors = vtkImageMapToColors::New();
        //image_map_to_colors->SetLookupTable(lookup_table);
        //image_map_to_colors->SetInputConnection(image_slab_reslice->GetOutputPort());
        
        image_actor = vtkImageActor::New();
        //image_actor->GetMapper()->SetInputConnection(image_map_to_colors->GetOutputPort());
        image_actor->GetMapper()->SetInputConnection(image_shift_scale->GetOutputPort());
        
        renderer = vtkSmartPointer<vtkRenderer>::New();
        renderer->AddActor(image_actor);
        
        render_window = vtkRenderWindow::New();
        render_window->SetOffScreenRendering(1);
        render_window->AddRenderer(renderer);
        render_window->SetSize(512,512);
        render_window->Render();
    }
    
    
} // namespace image_data_service

