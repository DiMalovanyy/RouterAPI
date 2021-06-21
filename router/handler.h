#ifndef HANDLER_H
#define HANDLER_H


#include "precompiled.h"


class HttpHandler {
public:

    HttpHandler() {}
    
    virtual void Process(boost::beast::http::response<boost::beast::http::string_body>&,
                         const boost::beast::http::request<boost::beast::http::string_body>&) = 0;


protected:
    //Some db instance
};


class SayHelloHandler: public HttpHandler {
public:
    SayHelloHandler() : HttpHandler() {}
    
    void Process(boost::beast::http::response<boost::beast::http::string_body>& responseWriter, const const boost::beast::http::request<boost::beast::http::string_body>& request) override {
        responseWriter.body().append("Hello world!");
        responseWriter.result(200);
    }
};


#endif
