#include "stdafx.h"
//
//  volume_loader.cpp
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/25/14.
//
//

#include "volume_loader.h"
#include "log.h"

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>
#include <boost/timer/timer.hpp>

namespace image_data_service {
    
    vtkSmartPointer<vtkImageData> volume_loader::load_volume_from_dicom(const std::string& path)
    {
        LOG_VERBOSE(1) << "volume_loader::load_volume_from_dicom(" + path + ")";
        
        boost::timer::auto_cpu_timer t;

        vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
        reader->SetDirectoryName(path.c_str());
        reader->Update();
        vtkSmartPointer<vtkImageData> imageData(reader->GetOutput());

        double xSpacing, ySpacing, zSpacing;
        imageData->GetSpacing(xSpacing, ySpacing, zSpacing);
        
        int* dims = imageData->GetDimensions();
        
        double xCenter = dims[0] * xSpacing / 2.0;
        double yCenter = dims[1] * ySpacing / 2.0;
        double zCenter = dims[2] * zSpacing / 2.0;

        imageData->SetOrigin(-xCenter, -yCenter, -zCenter);

        
        return imageData;
    }

    
} // namespace image_data_service
