#ifndef POSTGRES_COUNTRY_REPO_H
#define POSTGRES_COUNTRY_REPO_H

#include "repos.h"

#include <memory>
#include <pqxx/pqxx>

class PostgresCountryRepo final: public CountryRepo {
public:
    
    PostgresCountryRepo(std::unique_ptr<pqxx::work>& dbInstance) : _dbInstance(dbInstance) {}
    
    Country countryById(size_t) const override {
        
        return {};
    }
    
private:
    std::unique_ptr<pqxx::work>& _dbInstance;
    
};

#endif
