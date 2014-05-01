//
//  status_request_handler.cpp
//  cornerstoneVisualizationService
//
//  Created by Chris Hafey on 4/24/14.
//
//

#include "status_request_handler.h"
#include "system_status.h"
#include "json_reply.h"
#include "json_property_tree.h"

#include "../http_server/reply.hpp"
#include "../http_server/request.hpp"
#include "../http_server/url.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <sstream>
#include <fstream>
#include <string>


using boost::property_tree::ptree;
using image_data_service::json_property_tree::put;

namespace image_data_service {
    
    void status_request_handler::handle_request(const http::server::request& req, http::server::reply& rep)
    {
        // Decode url to path.
        std::string request_path;
        if (!http::server::url::decode(req.uri, request_path))
        {
            rep = http::server::reply::stock_reply(http::server::reply::bad_request);
            return;
        }
        
        system_status& ss = system_status::instance();
        
        ptree pt;
        pt.put("uptime", boost::posix_time::to_simple_string(ss.uptime()));
        
        // return a summary of activity over the past 30 seconds
        boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

        const int maxSeconds = 10;
        
        const std::vector<render_history_item>& history = ss.history();
        int index =  history.size() -1;
        std::map<int, int> summary;
        while(index >= 0)
        {
            const render_history_item& hi = history[index];
            boost::posix_time::time_duration timeAgo = now - hi.render_ptime;
            long totalSeconds = timeAgo.total_seconds();
            if(totalSeconds > maxSeconds)
            {
                break;
            }
            summary[totalSeconds]++;

            index--;
        }

        ptree arrayElement;
        ptree arrayChild;

        for(int i=0; i < maxSeconds; i++) {
            put(arrayElement, "count", summary[i]);
            arrayChild.push_back(std::make_pair("",arrayElement));
        }
        
        pt.put_child(ptree::path_type("render_history"), arrayChild);
        
        json_reply::write(rep, pt, true);
    }
    
} // namespace image_data_service
