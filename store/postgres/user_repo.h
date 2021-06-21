#ifndef POSTGRES_USER_REPO_H
#define POSTGRES_USER_REPO_H

#include "repos.h"

#include <memory>
#include <pqxx/pqxx>

class PostgresUserRepo final: public UserRepo {
public:
    
    PostgresUserRepo(std::unique_ptr<pqxx::work>& dbInstance) : _dbInstance(dbInstance) {}
    
    
    User userById(size_t) const override {
        
        return {};
    }
    
private:
    std::unique_ptr<pqxx::work>& _dbInstance;
    
};


#endif
