#ifndef POSTGRES_CITY_REPO_H
#define POSTGRES_CITY_REPO_H

#include "repos.h"

#include <memory>
#include <pqxx/pqxx>

class PostgresCityRepo final : public CityRepo {
public:
    
    PostgresCityRepo(std::unique_ptr<pqxx::work>& dbInstance) : _dbInstance(dbInstance) {}
    
    City cityById(size_t) const override {
        
        return {};
    }
    
private:
    std::unique_ptr<pqxx::work>& _dbInstance;
};

#endif
