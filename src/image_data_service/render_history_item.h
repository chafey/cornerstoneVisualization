//
//  render_history_item.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__render_history_item__
#define __cornerstoneVisualizationService__render_history_item__

// headers from this project
// headers from other projects
// headers from vtk
// headers from boost
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/local_time/local_time.hpp>
// headers from stdlib
#include <string>

// forward declarations


namespace image_data_service {
    
    struct render_history_item
    {
        // the uri that triggered the render activity
        std::string url;
        
        // the date/time this render event started
        boost::posix_time::ptime render_ptime;
        
        // how long it took for the render even to complete
        boost::posix_time::time_duration render_duration;
        
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__render_history_item__) */

