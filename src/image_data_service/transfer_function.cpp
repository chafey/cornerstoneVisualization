#include "stdafx.h"
#include "transfer_function.h"
// include headers from this project
// include headers from other projects
// include vtk headers
// include boost headers
// include stdlib headers

namespace image_data_service {
    
    
    transfer_function::transfer_function()
    :   name_(),
        opacity_(vtkSmartPointer<vtkPiecewiseFunction>::New()),
        color_(vtkSmartPointer<vtkColorTransferFunction>::New())
    {
    }
    
    transfer_function::transfer_function(const std::string& name)
    :   name_(name),
        opacity_(vtkSmartPointer<vtkPiecewiseFunction>::New()),
        color_(vtkSmartPointer<vtkColorTransferFunction>::New())
    {
    }
    
    transfer_function::transfer_function(
        const std::string& name,
        vtkSmartPointer<vtkPiecewiseFunction> opacity,
        vtkSmartPointer<vtkColorTransferFunction> color)
    :   name_(name),
        opacity_(opacity),
        color_(vtkSmartPointer<vtkColorTransferFunction>::New())
    {
        
    }

    
} // namespace image_data_service

