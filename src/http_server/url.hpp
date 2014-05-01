//
// url.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_SERVER_URL_HPP
#define HTTP_SERVER_URL_HPP

#include <string>
#include <boost/noncopyable.hpp>

namespace http {
    namespace server {
        
        class url
        : private boost::noncopyable
        {
        public:
            
            static bool decode(const std::string& in, std::string& out);
            
        };
        
    } // namespace server
} // namespace http

#endif // HTTP_REQUEST_HANDLER_HPP