#include "stdafx.h"
//
// request_router.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_router.hpp"
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"
#include "url.hpp"
#include "request_handler.hpp"

namespace http {
    namespace server {
        
        static std::map<const std::string, request_handler*> request_handlers;
        
        void request_router::register_handler(const std::string& path, request_handler* handler)
        {
            request_handlers[path] = handler;
        }

        request_router::request_router()
        {
            
        }
        
        void encode(std::string& data) {
            std::string buffer;
            buffer.reserve(data.size());
            for(size_t pos = 0; pos != data.size(); ++pos) {
                switch(data[pos]) {
                    case '&':  buffer.append("&amp;");       break;
                    case '\"': buffer.append("&quot;");      break;
                    case '\'': buffer.append("&apos;");      break;
                    case '<':  buffer.append("&lt;");        break;
                    case '>':  buffer.append("&gt;");        break;
                    default:   buffer.append(&data[pos], 1); break;
                }
            }
            data.swap(buffer);
        }

        
        void request_router::handle_request(const request& req, reply& rep)
        {
            // Decode url to path.
            std::string request_path;
            if (!http::server::url::decode(req.uri, request_path))
            {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }
            
            // Request path must be absolute and not contain "..".
            if (request_path.empty() || request_path[0] != '/'
                || request_path.find("..") != std::string::npos)
            {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }
            
            std::map<const std::string, request_handler*>::iterator ri = request_handlers.begin();
            while(ri != request_handlers.end()) {
                if(boost::starts_with(request_path, ri->first))
                {
                    try {
                        ri->second->handle_request(req, rep);
                    }
                    catch(std::exception& e) {
                        std::string html =
                        "<html>"
                        "<head><title>Internal Server Error</title></head>"
                        "<body><h1>500 Internal Server Error</h1>"
                        "<pre>";
                        std::string what = e.what();
                        encode(what);

                        html += what;
                        html+= "</pre></body></html>";
                        
                        
                        std::cout << e.what();
                        
                        rep.status = reply::internal_server_error;
                        rep.content =html.c_str();
                        rep.headers.resize(2);
                        rep.headers[0].name = "Content-Length";
                        rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
                        rep.headers[1].name = "Content-Type";
                        rep.headers[1].value = "text/html";

                        //rep = reply::stock_reply(reply::internal_server_error);
                    }
                    catch(...) {
                        rep = reply::stock_reply(reply::internal_server_error);
                    }
                    return;
                }
                ri++;
            }
        }
        
        
    } // namespace server
} // namespace http