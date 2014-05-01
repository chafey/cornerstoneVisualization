//
// query_parser.hpp
// ~~~~~~~~~
//
// Copyright (c) 2014 Chris Hafey (chafey@gmail.com)
//

#ifndef HTTP_QUERY_PARSER_HPP
#define HTTP_QUERY_PARSER_HPP

#include <string>
#include <map>

namespace http {
    namespace server {
        namespace query_parser {
        
            std::map<std::string, std::string> parse(const std::string& query);

        } // namespace query_parser
    } // namespace server
} // namespace http

#endif // HTTP_REPLY_HPP