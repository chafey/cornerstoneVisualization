//
//  volume_loader.h
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/25/14.
//
//

#ifndef __cornerstoneVisualizationService__volume_loader__
#define __cornerstoneVisualizationService__volume_loader__

#include <string>
#include <boost/noncopyable.hpp>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

namespace image_data_service {
    
    class volume_loader : boost::noncopyable
    {
    public:
        
        /// Load a volume from dicom files in a folder
        vtkSmartPointer<vtkImageData> load_volume_from_dicom(const std::string& path);
        
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__volume_loader__) */
