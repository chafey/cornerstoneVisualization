//
//  render_event.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__render_event__
#define __cornerstoneVisualizationService__render_event__

// headers from this project

// headers from other projects
// headers from vtk
// headers from boost
#include <boost/noncopyable.hpp>
// headers from stdlib
#include <string>

// forward declarations


namespace image_data_service {
    
    struct render_history_item;
    
    class render_event : boost::noncopyable
    {
    public:
        explicit render_event(const std::string url);
        
        ~render_event();
        
    private:
        render_history_item* render_history_item_;
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__render_event__) */

