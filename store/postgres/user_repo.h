#ifndef POSTGRES_USER_REPO_H
#define POSTGRES_USER_REPO_H

#include "repos.h"

class PostgresUserRepo final: public UserRepo {
public:
    
    User userById(size_t) const override {
        
        return {};
    }
    
};


#endif
