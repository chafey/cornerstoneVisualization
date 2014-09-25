#include "stdafx.h"
#include "render_event.h"

// include headers from this project
#include "render_history_item.h"
#include "system_status.h"

// include headers from other projects
// include vtk headers
// include boost headers
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/local_time/local_time.hpp>
// include stdlib headers


namespace image_data_service {
    
    render_event::render_event(const std::string url)
    {
        render_history_item_ = new render_history_item();
        render_history_item_->url = url;
        render_history_item_->render_ptime = boost::posix_time::second_clock::local_time();
    }
    
    render_event::~render_event()
    {
        render_history_item_->render_duration = boost::posix_time::second_clock::local_time() - render_history_item_->render_ptime;
        system_status::instance().add(*render_history_item_);
    }
    
    
    
} // namespace image_data_service

