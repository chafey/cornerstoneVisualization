#include "stdafx.h"
//
// query_parser.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2014 Chris Hafey (chafey@gmail.com)
//


#include "query_parser.hpp"

namespace http {
    namespace server {
        namespace query_parser {
            
            void parseNameAndValue(const std::string& nameAndValue, std::map<std::string, std::string>& parameters)
            {
                size_t equalPos = nameAndValue.find("=");
                std::string paramName = nameAndValue.substr(0, equalPos);
                std::string paramValue = nameAndValue.substr(equalPos+1);
                parameters[paramName] = paramValue;
            }
            
            std::map<std::string, std::string> parse(const std::string& query)
            {
                std::map<std::string, std::string> parameters;
                
                std::string s = query;
                std::string delimiter = "&";
                
                size_t pos = 0;
                std::string nameAndValue;
                while ((pos = s.find(delimiter)) != std::string::npos) {
                    nameAndValue = s.substr(0, pos);
                    parseNameAndValue(nameAndValue, parameters);
                    s.erase(0, pos + delimiter.length());
                }
                parseNameAndValue(s, parameters);
                
                return parameters;
            }
            
        } // namespace query_parser
    } // namespace server
} // namespace http