#ifndef REQUEST_PROCESSOR_H
#define REQUEST_PROCESSOR_H


#include <boost/beast.hpp>
#include <spdlog/spdlog.h>

// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
template< class Body, class Allocator, class Send>
void handleRequest(boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>>&& req, Send&& send) {
    spdlog::get("console") -> info("The request start processing...");
    
//    RequestProcessor<Body> processor(std::move(req));
    
//    send(std::move(processor.getResponse()));
}


#endif
