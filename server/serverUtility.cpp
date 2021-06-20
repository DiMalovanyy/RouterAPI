#include "serverUtility.h"
#include <exception>

#include <spdlog/spdlog.h>

void fail(const boost::beast::error_code& error_code, const std::string& message) {
    spdlog::get("console") -> error("code = {0}. Message: {1}. With lable: {2}", error_code.value(), error_code.message(), message);
    
    throw std::logic_error(error_code.message());
}
