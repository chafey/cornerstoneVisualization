//
//  transfer_function.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__transfer_function__
#define __cornerstoneVisualizationService__transfer_function__

// headers from this project
// headers from other projects
// headers from vtk
#include <vtkSmartPointer.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
// headers from boost
#include <boost/noncopyable.hpp>
// headers from stdlib
#include <string>

// forward declarations


namespace image_data_service {
    
    // transfer functions consist of an opacity table and a color table
    class transfer_function : boost::noncopyable
    {
    public:
        explicit transfer_function();
        explicit transfer_function(const std::string& name);
        explicit transfer_function(const std::string& name, vtkSmartPointer<vtkPiecewiseFunction> opacity, vtkSmartPointer<vtkColorTransferFunction> color);
        
        // the opacity table for this transfer function
        vtkSmartPointer<vtkPiecewiseFunction> opacity() {return opacity_;}
        const vtkSmartPointer<vtkPiecewiseFunction> opacity() const {return opacity_;}

        // the color table for this transfer function
        vtkSmartPointer<vtkColorTransferFunction> color() {return color_;}
        const vtkSmartPointer<vtkColorTransferFunction> color() const {return color_;}
        
        // the name of this transfer function
        const std::string& name() {return name_;}
        
    private:
        std::string name_;
     
        vtkSmartPointer<vtkPiecewiseFunction> opacity_;
        
        vtkSmartPointer<vtkColorTransferFunction> color_;
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__transfer_function__) */

