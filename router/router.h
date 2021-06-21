#ifndef ROUTER_H
#define ROUTER_H

#include <iostream>
#include <type_traits>
#include <unordered_map>

#include "precompiled.h"



#include "handler.h"

class HttpRouter {
public:
    
    explicit HttpRouter() = default;
    
    
    void AddHandler(const std::string& endpoint, std::unique_ptr<HttpHandler> handler) {
        _router.insert(std::make_pair(endpoint, std::move(handler)));
    }
    
    
    // template <typename Fields, typename Body >
    // boost::beast::http::response<Fields, Body> getResponse() {
        
    // }

    boost::beast::http::response<boost::beast::http::string_body> getResponse( 
        const boost::beast::http::request<boost::beast::http::string_body>& request
    ) const {

        boost::beast::http::response<boost::beast::http::string_body> response;
        response.version(11);
        response.set(boost::beast::http::field::server, "Beast Http server");
        //Get endpoint and method from request
        std::string endpoint = std::string(request.target().data());
        std::cout << "Endpoint: " << endpoint << std::endl;
        //Match with router. if does not found return back 404
        if (_router.find(endpoint) == _router.end()) {
            response.result(boost::beast::http::status::not_found);
        } else {
            _router.at(endpoint) -> Process(response, request);
        }
        
        response.prepare_payload();
        return response;
    }
    
    
    
private:
    std::unordered_map<std::string, std::unique_ptr<HttpHandler>> _router;
};


#endif
