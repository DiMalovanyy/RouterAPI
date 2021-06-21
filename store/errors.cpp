
#include "errors.h"
#include <string>


StoreException::StoreException(Error errorCode) : std::exception(), _errorCode(errorCode) {}

const std::map<StoreException::Error, std::string> StoreException::error_description = {
    {StoreException::EMPTY_RESPONSE, "No data was returned by query"},
    {StoreException::UNDEFINED, "Some undefined error"}
};

const char * StoreException::what() const noexcept {
    return error_description.at(_errorCode).c_str();
}
