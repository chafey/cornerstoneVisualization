//
// request_handler.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_SERVER_FILE_REQUEST_HANDLER_HPP
#define HTTP_SERVER_FILE_REQUEST_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>
#include "request_handler.hpp"

namespace http {
    namespace server {
        
        struct reply;
        struct request;
        
        /// The common handler for all incoming requests.
        class file_request_handler
        : public request_handler
        {
        public:
            
            explicit file_request_handler(const std::string& doc_root);
            
            /// Handle a request and produce a reply.
            virtual void handle_request(const request& req, reply& rep);
            
        private:
            /// The directory containing the files to be served.
            std::string doc_root_;

            
        };
        
    } // namespace server
} // namespace http

#endif // HTTP_SERVER_FILE_REQUEST_HANDLER_HPP