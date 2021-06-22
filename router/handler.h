#ifndef HANDLER_H
#define HANDLER_H


#include "precompiled.h"

#include "store/store.h"


class HttpHandler {
public:
    
    HttpHandler(std::unique_ptr<Store>& store): _store(store) {}
    
    virtual void Process(boost::beast::http::response<boost::beast::http::string_body>&,
                         const boost::beast::http::request<boost::beast::http::string_body>&,
                         const std::optional<std::string>) = 0;
    
    
    
    void respond()


protected:
    std::unique_ptr<Store>& _store;
};


class SayHelloHandler: public HttpHandler {
public:
    SayHelloHandler(std::unique_ptr<Store>& store) : HttpHandler(store) {}
    
    void Process(boost::beast::http::response<boost::beast::http::string_body>& responseWriter, const const boost::beast::http::request<boost::beast::http::string_body>& request, const std::optional<std::string> param = std::nullopt ) override {
        responseWriter.body().append("Hello world!");
        responseWriter.result(200);
    }
};


class GetUserByIdHandler: public HttpHandler {
public:
    GetUserByIdHandler(std::unique_ptr<Store>& store) : HttpHandler(store) {}
    
    void Process(boost::beast::http::response<boost::beast::http::string_body>& responseWriter, const const boost::beast::http::request<boost::beast::http::string_body>& request, const std::optional<std::string> param = std::nullopt ) override {
        
        auto method = request.method();
        
        switch (request.method()) {
            case boost::beast::http::verb::get: {
                try {
                    User user = _store -> User() -> userById(atoi(param -> data()));
                    responseWriter.body().append("Hello: " + user.name);
                } catch (...) {
                    std::cout << "Some errors occured" << std::endl;
                }
                break;
            }
            case boost::beast::http::verb::post: {
                
                std::cout << "Method post" << std::endl;
                break;
            }
            default: std::logic_error("Unsupported method");
        }
        responseWriter.result(200);
    }
};


class GetAllUsers: public HttpHandler {
public:
    GetAllUsers(std::unique_ptr<Store>& store) : HttpHandler(store) {}
    
    void Process(boost::beast::http::response<boost::beast::http::string_body>& responseWriter, const const boost::beast::http::request<boost::beast::http::string_body>& request, const std::optional<std::string> param = std::nullopt ) override {
        responseWriter.body().append("All users!");
        responseWriter.result(200);
    }
};


#endif
