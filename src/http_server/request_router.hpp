//
// request_router.hpp
// ~~~~~~~~~~~~~~~~~~~
//

#ifndef HTTP_REQUEST_ROUTER_HPP
#define HTTP_REQUEST_ROUTER_HPP

#include <string>
#include <boost/noncopyable.hpp>

namespace http {
    namespace server {
        
        struct reply;
        struct request;
        class request_handler;
        
        /// The common handler for all incoming requests.
        class request_router
        : private boost::noncopyable
        {
        public:
            /// Construct with a directory containing files to be served.
            request_router();
            
            /// Handle a request and produce a reply.
            void handle_request(const request& req, reply& rep);
            
            static void register_handler(const std::string& path, request_handler* handler);
            
        private:
            
        };
        
    } // namespace server
} // namespace http

#endif // HTTP_REQUEST_HANDLER_HPP