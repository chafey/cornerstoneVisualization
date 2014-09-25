#include "stdafx.h"
#include "volume.h"
// include headers from this project
#include "log.h"
// include headers from other projects
// include vtk headers
#include <vtkImageData.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
// include boost headers
// include stdlib headers

namespace image_data_service {
    
    
    volume::volume(vtkSmartPointer<vtkImageData> imageData)
    : image_data_(imageData)
    {
        //double valuesRange[2];
        //vtkDoubleArray::SafeDownCast(_image_data->GetPointData()->GetArray("ImageScalars"))->GetValueRange(valuesRange);
        //std::cout << "valuesRange = " << valuesRange[0] << " " << valuesRange[1] << std::endl;
        
        //min_value = valuesRange[0];
        //max_value = valuesRange[1];

		int dims[3];
		imageData->GetDimensions(dims);
		
		double spacing[3];
		imageData->GetSpacing(spacing);
		
		sizeInMM[0] = dims[0] * spacing[0];
		sizeInMM[1] = dims[1] * spacing[1];
		sizeInMM[2] = dims[2] * spacing[2];

		max_radius = sqrt(sizeInMM[0] * sizeInMM[0] + sizeInMM[1] * sizeInMM[1] + sizeInMM[2] * sizeInMM[2]) / 2.0;
	}
    
    boost::shared_ptr<struct mpr_renderer> volume::mpr_renderer()
    {
        if (mpr_renderer_.get() == 0)
        {
            mpr_renderer_ = boost::shared_ptr<struct mpr_renderer>(new struct mpr_renderer(image_data_));
        }
        return mpr_renderer_;
    }
    
    boost::shared_ptr<struct volume_renderer> volume::volume_renderer(int width, int height)
    {
        // if the volume renderer hasn't been created yet, create it now
        if(volume_renderer_.get() == 0)
        {
            volume_renderer_ = boost::shared_ptr<struct volume_renderer>(new struct volume_renderer(image_data_, width, height));
        }
        // if the created volume renderer can't support this height/width, create a new one
        if(volume_renderer_->max_width < width ||
           volume_renderer_->max_height < height)
        {
            LINFO << "volume::volume_renderer() - larger width/height requested, creating new volume_renderer";
            volume_renderer_ = boost::shared_ptr<struct volume_renderer>(new struct volume_renderer(image_data_, width, height));
        }
        return volume_renderer_;
    }
    
} // namespace image_data_service

