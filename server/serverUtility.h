#ifndef SERVER_UTILITY_H
#define SERVER_UTILITY_H

#include <string>
#include <boost/beast.hpp>


void fail(const boost::beast::error_code& error_code, const std::string& message);

#endif
