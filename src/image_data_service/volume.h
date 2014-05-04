//
//  volume.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__volume__
#define __cornerstoneVisualizationService__volume__

// headers from this project
#include "mpr_renderer.h"
#include "volume_renderer.h"

// headers from other projects
// headers from vtk
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

// headers from boost
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

// headers from stdlib
#include <string>

// forward declarations



namespace image_data_service {
    
    class volume : boost::noncopyable
    {
    public:
        explicit volume(vtkSmartPointer<vtkImageData> imageData);
        
        std::string volumeId;
        
        // double min_value;
        
        // double  max_value;

        vtkSmartPointer<vtkImageData> image_data() {return image_data_;}
        
        boost::shared_ptr<struct mpr_renderer> mpr_renderer();
        
        boost::shared_ptr<struct volume_renderer> volume_renderer(int width, int height);
        
		// the distance from the center of the volume to the farthest corner
		double max_radius;

		// the size in MM of the volume x,y,z
		double sizeInMM[3];

	private:
        
        vtkSmartPointer<vtkImageData> image_data_;

        boost::shared_ptr<struct mpr_renderer> mpr_renderer_;
        
        boost::shared_ptr<struct volume_renderer> volume_renderer_;

    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__volume__) */

