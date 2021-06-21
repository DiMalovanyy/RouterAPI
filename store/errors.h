#ifndef STORE_ERRORS_H
#define STORE_ERRORS_H

#include <exception>
#include <map>

class StoreException final : public std::exception {
public:

    enum Error {
        EMPTY_RESPONSE,
        UNDEFINED
    };
    
    StoreException(Error errorCode);
    
    static const std::map<Error, std::string> error_description;
    
    const char * what() const noexcept override;
    
private:
    Error _errorCode;
};


#endif
