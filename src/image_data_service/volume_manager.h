//
//  volume_manager.h
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/25/14.
//
//

#ifndef __cornerstoneVisualizationService__volume_manager__
#define __cornerstoneVisualizationService__volume_manager__

#include "volume.h"

#include <boost/noncopyable.hpp>
#include <string>
#include <map>

namespace image_data_service {
    
    class volume_manager : boost::noncopyable
    {
    public:
        
        // returns the singleton instance
        static volume_manager& instance();

        // the path to where dicom volumes are stored
        const std::string& dicom_volume_root() const {return dicom_volume_root_;}
        void dicom_volume_root(const std::string& path) {dicom_volume_root_ = path;}

        // the path to where volumes are cached
        const std::string& volume_root() const {return volume_root_;}
        void volume_root(const std::string& path) {volume_root_ = path;}
        
        // returns true if volumeId is currently in the cache
        bool is_cached(const std::string &volumeId);
        
        // returns the volume for the specified volumeId
        volume& get(const std::string& volumeId);
        
        // returns a list of loaded volumes
        std::vector<volume*> loaded_volumes();
        
    private:
        volume_manager();
        
        std::map<std::string, volume*> volumes_;
        std::string volume_root_;
        std::string dicom_volume_root_;
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__volume_manager__) */
