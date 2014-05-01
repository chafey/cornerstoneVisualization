//
//  render_window_manager.cpp
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/25/14.
//
//

#include "render_window_manager.h"

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

#include <boost/timer/timer.hpp>

namespace image_data_service {
    
    static render_window_manager* rwm = 0;
    
    render_window_manager& render_window_manager::get()
    {
        if(rwm == 0) {
            rwm = new render_window_manager();
        }
        return *rwm;
    }
    
    render_window_manager::render_window_manager()
    {
    }
    
    /// returns true if volumeId is currently in the cache
    bool render_window_manager::is_cached(const std::string &volumeId)
    {
        return render_windows_.find(volumeId) != render_windows_.end();
    }
    
    /// reads a volume from the cache
    vtkSmartPointer<vtkRenderWindow> render_window_manager::read(const std::string& volumeId)
    {
        return render_windows_[volumeId];
    }
    
    /// writes a volume to the cache
    void render_window_manager::write(const std::string& volumeId, vtkSmartPointer<vtkRenderWindow> imageData)
    {
        render_windows_[volumeId] = imageData;
    }
    
    
} // namespace image_data_service
