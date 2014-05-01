//
//  render_window_manager.h
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/25/14.
//
//

#ifndef __cornerstoneVisualizationService__render_window_manager__
#define __cornerstoneVisualizationService__render_window_manager__

#include <string>
#include <boost/noncopyable.hpp>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <map>

namespace image_data_service {
    
    /// The common handler for all incoming requests.
    class render_window_manager : boost::noncopyable
    {
    public:
        /// Construct with a directory containing files to be served.
        explicit render_window_manager();
        
        /// returns true if volumeId is currently in the cache
        bool is_cached(const std::string &volumeId);
        
        /// reads a volume from the cache
        vtkSmartPointer<vtkRenderWindow> read(const std::string& volumeId);
        
        /// writes a volume to the cache
        void write(const std::string& volumeId, vtkSmartPointer<vtkRenderWindow> imageData);
        
        static render_window_manager& get();
        
    private:
        std::map<std::string, vtkSmartPointer<vtkRenderWindow> > render_windows_;
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__render_window_manager__) */
