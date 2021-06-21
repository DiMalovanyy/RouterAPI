#ifndef REQUEST_PROCESSOR_H
#define REQUEST_PROCESSOR_H
#include <iostream>


#include "precompiled.h"

#include "router.h"

// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
template< class Allocator, class Send>
void handleRequest(
                   boost::beast::http::request<boost::beast::http::string_body,
                   boost::beast::http::basic_fields<Allocator>>&& req,
                   Send&& send,
                   const std::unique_ptr<HttpRouter>& router) {
    
    spdlog::get("console") -> info("The request start processing...");
    // std::cout << "start processing" << std::endl;

    
    send(std::move(router -> getResponse(std::move(req))));
}


#endif
