//
//  volume_manager.cpp
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/25/14.
//
//

#include "volume_manager.h"
#include "volume_cache.h"
#include "volume_loader.h"
#include "log.h"

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

#include <boost/timer/timer.hpp>

namespace image_data_service {
    
    static volume_manager* vm;
    
    volume_manager& volume_manager::instance()
    {
        if(vm == 0) {
            vm = new volume_manager();
        }
        return *vm;
    }

    volume_manager::volume_manager()
    : volume_root_("VolumeCache")
    {
    }
    
    volume& volume_manager::get(const std::string& volumeId)
    {
        LOG_VERBOSE(1) << "volume_manager::get(" << volumeId << ")";

        // check in memory cache
        if(is_cached(volumeId))
        {
            return *volumes_[volumeId];
        }
        
        // check the disk cache
        volume_cache vc(volume_root_);
        if(vc.is_cached(volumeId)) {
            vtkSmartPointer<vtkImageData> imageData = vc.read(volumeId);
            volumes_[volumeId] = new volume(imageData);
            volumes_[volumeId] ->volumeId = volumeId;
            return *volumes_[volumeId];
        }

        // Load from dicom
        volume_loader vl;
        vtkSmartPointer<vtkImageData> imageData = vl.load_volume_from_dicom(volume_root_ + volumeId + "/");
        vc.write(volumeId, imageData);
        volumes_[volumeId] = new volume(imageData);
        volumes_[volumeId] ->volumeId = volumeId;
        return *volumes_[volumeId];
    }
    
    bool volume_manager::is_cached(const std::string &volumeId)
    {
        return volumes_.find(volumeId) != volumes_.end();
    }
    
    std::vector<volume*> volume_manager::loaded_volumes()
    {
        std::vector<volume*> volumes;
     
        std::map<std::string, volume*>::iterator iter = volumes_.begin();
        while(iter != volumes_.end()) {
            volumes.push_back(iter->second);
            ++iter;
        }

        return volumes;
    }

    
} // namespace image_data_service
