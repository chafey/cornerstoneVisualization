//
//  system_status.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__system_status__
#define __cornerstoneVisualizationService__system_status__
// headers from this project
#include "render_history_item.h"
// headers from other projects
// headers from vtk
// headers from boost
#include <boost/noncopyable.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/local_time/local_time.hpp>

// headers from stdlib
#include <string>
#include <vector>

// forward declarations


namespace image_data_service {

    class system_status : boost::noncopyable
    {
    public:
        
        static system_status& instance();
        
        // returns the uptime for this process
        boost::posix_time::time_duration uptime()
        {
            boost::posix_time::ptime now(boost::posix_time::second_clock::local_time());
            return now - start_time_;
        }
        
        // returns the rendering history
        const std::vector<render_history_item>& history()
        {
            return history_;
        }
        
        // adds an item to the rendering history
        void add(const render_history_item& item)
        {
            history_.push_back(item);
        }
        
        
    private:
        system_status();
        
        boost::posix_time::ptime start_time_; // the date/time this system started
        
        std::vector<render_history_item> history_;
        
    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__system_status__) */

