//
//  volume_cache.h
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/25/14.
//
//

#ifndef __cornerstoneVisualizationService__volume_cache__
#define __cornerstoneVisualizationService__volume_cache__

#include <string>
#include <boost/noncopyable.hpp>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

namespace image_data_service {
    
    /// The common handler for all incoming requests.
    class volume_cache : boost::noncopyable
    {
    public:
        /// Construct with a directory containing files to be served.
        explicit volume_cache(const std::string& volumeRoot);
        
        /// returns true if volumeId is currently in the cache
        bool is_cached(const std::string &volumeId);
        
        /// reads a volume from the cache
        vtkSmartPointer<vtkImageData> read(const std::string& volumeId);

        /// writes a volume to the cache
        void write(const std::string& volumeId, vtkSmartPointer<vtkImageData> imageData);
    private:
        
        std::string volume_root_;
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__volume_cache__) */
