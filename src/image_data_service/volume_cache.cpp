//
//  volume_cache.cpp
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/25/14.
//
//

#include "volume_cache.h"
#include "log.h"

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkXMLImageDataReader.h>

#include <boost/filesystem.hpp>
#include <boost/timer/timer.hpp>

namespace image_data_service {
    
    
    volume_cache::volume_cache(const std::string& volumeRoot)
    : volume_root_(volumeRoot)
    {
    }
    
    static std::string make_volume_path(const std::string& volumeRoot, const std::string& volumeId)
    {
        boost::filesystem::path volumePath(volumeRoot);
        volumePath += "/" + volumeId;
        return volumePath.string();
    }
    
    /// returns true if volumeId is currently in the cache
    bool volume_cache::is_cached(const std::string &volumeId)
    {
        std::string fileName = make_volume_path(volume_root_, volumeId);
        return boost::filesystem::exists( fileName );
    }
    
    /// reads a volume from the cache
    vtkSmartPointer<vtkImageData> volume_cache::read(const std::string& volumeId)
    {
        LOG_VERBOSE(1) << "volume_cache::read(" + volumeId + ")";

        vtkSmartPointer<vtkXMLImageDataReader> reader = vtkSmartPointer<vtkXMLImageDataReader>::New();
        std::string fileName = make_volume_path(volume_root_, volumeId);
        reader->SetFileName(fileName.c_str());
        reader->Update();
        vtkSmartPointer<vtkImageData> imageData(reader->GetOutput());
        
        return imageData;
    }
    
    /// writes a volume to the cache
    void volume_cache::write(const std::string& volumeId, vtkSmartPointer<vtkImageData> imageData)
    {
        LOG_VERBOSE(1) << "volume_cache::write(" + volumeId + ")";
        
        vtkSmartPointer<vtkXMLImageDataWriter> writer = vtkSmartPointer<vtkXMLImageDataWriter>::New();
        std::string fileName = make_volume_path(volume_root_, volumeId);
        writer->SetFileName(fileName.c_str());
        writer->SetInputData(imageData);
        writer->Write();
    }

    
} // namespace image_data_service
