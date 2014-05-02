#include "system_status.h"
// include headers from this project
// include headers from other projects
// include vtk headers
// include boost headers
// include stdlib headers

namespace image_data_service {
    static system_status* ss = 0;
    
    
    system_status& system_status::instance()
    {
        if(ss == 0) {
            ss = new system_status();
        }
        return *ss;
    }
    
    system_status::system_status()
    {
        start_time_ = boost::posix_time::second_clock::local_time();
    }

} // namespace image_data_service

