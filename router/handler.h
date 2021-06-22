#ifndef HANDLER_H
#define HANDLER_H

#include <exception>

#include "precompiled.h"

#include "store/store.h"

//Rapidjson
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


inline std::string documentToSrting(rapidjson::Document&& doc) {
    std::string result;
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    return std::string(buffer.GetString(), buffer.GetSize());;
}


class HttpHandler {
public:
    
    HttpHandler(std::unique_ptr<Store>& store): _store(store) {}
    
    virtual void Process(boost::beast::http::response<boost::beast::http::string_body>&,
                         const boost::beast::http::request<boost::beast::http::string_body>&,
                         const std::optional<std::string>) = 0;
    
    
    void respond(boost::beast::http::response<boost::beast::http::string_body>& response, rapidjson::Document&& document, boost::beast::http::status status_code = boost::beast::http::status::ok) {
        response.set(boost::beast::http::field::content_type, "application/json");
        response.body().append(documentToSrting(std::move(document)));
        response.result(status_code);
    }
    
    void error(boost::beast::http::response<boost::beast::http::string_body>& response,
               std::exception_ptr exception,
               boost::beast::http::status status_code) {
        response.result(status_code);
        response.set(boost::beast::http::field::content_type, "application/json");
        
        try {
            std::rethrow_exception(exception);
        } catch (const std::exception& e) {
            response.body().append("{\"error\":\"" + std::string(e.what()) + "\"}");
            return;
        }
        response.body().append("{\"error\":\"empty error\"}");
    }


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
        try {
            switch (request.method()) {
                case boost::beast::http::verb::get: {
                    User user = _store -> User() -> userById(atoi(param -> data()));
                    rapidjson::Document doc;
                    doc.SetObject();
                    
                    rapidjson::Value jsonId(rapidjson::kObjectType);
                    jsonId.SetInt(user.id);
                    doc.AddMember("id", jsonId, doc.GetAllocator());
                    
                    rapidjson::Value jsonName(rapidjson::kStringType);
                    jsonName.SetString(user.name.data(), user.name.size(), doc.GetAllocator());
                    doc.AddMember("name", jsonName, doc.GetAllocator());
                    
                    respond(responseWriter, std::move(doc));
                    break;
                }
                case boost::beast::http::verb::post: {
                    
                    std::string body = request.body();
                    rapidjson::Document document;
                    document.Parse(body.c_str());
                    if (document.HasParseError()) {
                        throw std::logic_error("Response format: {\"name\": {name}}");
                    }
                    std::string username = document["name"].GetString();
                    int id = _store -> User() -> addUser(username);
                    
                    rapidjson::Document doc;
                    doc.SetObject();
                    
                    rapidjson::Value jsonStatus(rapidjson::kStringType);
                    std::string status = "User was successfully added with id: " + std::to_string(id);
                    jsonStatus.SetString(status.data(), status.size(), doc.GetAllocator());
                    doc.AddMember("status", jsonStatus, doc.GetAllocator());
                    
                    respond(responseWriter, std::move(doc));
                    break;
                }
                default: throw std::logic_error("Unsupported method");
            }
        } catch(...) {
            error(responseWriter, std::current_exception(), boost::beast::http::status::bad_request);
            return;
        }
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
