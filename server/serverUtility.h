#ifndef SERVER_UTILITY_H
#define SERVER_UTILITY_H

#include <string>
#include <boost/beast.hpp>


struct APIParams {
    size_t threadPoolSize;
    std::string host;
    std::string port;
    std::string databaseConnectionURL;
};


void fail(const boost::beast::error_code& error_code, const std::string& message);

#endif
