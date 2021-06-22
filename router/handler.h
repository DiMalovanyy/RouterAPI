#ifndef HANDLER_H
#define HANDLER_H


#include "precompiled.h"


class HttpHandler {
public:

    HttpHandler() {}
    
    virtual void Process(boost::beast::http::response<boost::beast::http::string_body>&,
                         const boost::beast::http::request<boost::beast::http::string_body>&,
                         const std::optional<std::string>) = 0;


protected:
    //Some db instance
};


class SayHelloHandler: public HttpHandler {
public:
    SayHelloHandler() : HttpHandler() {}
    
    void Process(boost::beast::http::response<boost::beast::http::string_body>& responseWriter, const const boost::beast::http::request<boost::beast::http::string_body>& request, const std::optional<std::string> param = std::nullopt ) override {
        responseWriter.body().append("Hello world!");
        responseWriter.result(200);
    }
};


class GetUserByIdHandler: public HttpHandler {
public:
    GetUserByIdHandler() : HttpHandler() {}
    
    void Process(boost::beast::http::response<boost::beast::http::string_body>& responseWriter, const const boost::beast::http::request<boost::beast::http::string_body>& request, const std::optional<std::string> param = std::nullopt ) override {
        
        responseWriter.body().append("Hello user: " + *param);
        
        responseWriter.result(200);
    }
};


class GetAllUsers: public HttpHandler {
public:
    GetAllUsers() : HttpHandler() {}
    
    void Process(boost::beast::http::response<boost::beast::http::string_body>& responseWriter, const const boost::beast::http::request<boost::beast::http::string_body>& request, const std::optional<std::string> param = std::nullopt ) override {
        responseWriter.body().append("All users!");
        responseWriter.result(200);
    }
};


#endif
