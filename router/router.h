#ifndef ROUTER_H
#define ROUTER_H

#include <iostream>
#include <vector>
#include <type_traits>
#include <unordered_map>
#include <optional>

//For split
#include <boost/algorithm/string.hpp>

#include "precompiled.h"



#include "handler.h"

class HttpRouter {
public:
    
    explicit HttpRouter() {
        
    }
    
    
    void AddHandler(const std::string& endpoint, std::unique_ptr<HttpHandler> handler) {
//        std::vector<std::string> splitedEndpoint;
//        boost::split(splitedEndpoint, endpoint, boost::is_any_of("/"));
//        _router[endpoint] = handler;
    
        _router.insert(std::make_pair(endpoint, std::move(handler)));
    }

    boost::beast::http::response<boost::beast::http::string_body> getResponse( 
        const boost::beast::http::request<boost::beast::http::string_body>& request
    ) const {

        boost::beast::http::response<boost::beast::http::string_body> response;
        response.version(11);
        response.set(boost::beast::http::field::server, "Beast Http server");
        //Get endpoint and method from request
        std::string endpoint = std::string(request.target().data());
        
        
        auto findString = mathcedEndpoint(std::string(request.target().data()));
        if (!findString) {
            response.result(boost::beast::http::status::not_found);
        } else {
            _router.at(findString -> first) -> Process(response, request, findString -> second);
        }
        
        
        response.prepare_payload();
        return response;
    }
    
    
    
private:
    
    std::optional<std::pair<std::string, std::string>> mathcedEndpoint(const std::string& endpoint) const {
//        std::cout << "Input endpoint: " << endpoint << std::endl;
        
        if (_router.find(endpoint) != _router.end()) {
            return std::make_pair(endpoint, "");
        }
        std::string catedEndpoint = std::string(endpoint.begin(), endpoint.end() - 1);
        if (_router.find(endpoint + "/") != _router.end()) {
            return std::make_pair(endpoint + "/", "");
        }
        
        if (_router.find(std::string(endpoint.begin(), endpoint.end() - 1)) != _router.end() ) {
            return std::make_pair(std::string(endpoint.begin(), endpoint.end() - 1), "");
        }
        
        std::vector<std::string> splitedEndpoint;
        boost::split(splitedEndpoint, endpoint, boost::is_any_of("/"));
        
        std::string lastParam = splitedEndpoint[splitedEndpoint.size() - 1];
//        std::cout << "last param: " << lastParam << std::endl;
        splitedEndpoint.pop_back();
        
        std::string findString = boost::algorithm::join(splitedEndpoint, "/") + "/{}";
        
//        std::cout << "String: " << findString << std::endl;
        
        if (_router.find(findString) != _router.end()) {
            return std::make_pair(findString, lastParam);
        }
        
        
        return std::nullopt;
    }
    
    std::unordered_map<std::string, std::unique_ptr<HttpHandler>> _router;
};


#endif
