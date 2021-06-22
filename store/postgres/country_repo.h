#ifndef POSTGRES_COUNTRY_REPO_H
#define POSTGRES_COUNTRY_REPO_H

#include "repos.h"

#include <memory>
#include <pqxx/pqxx>

class PostgresCountryRepo final: public CountryRepo {
public:
    
    PostgresCountryRepo(std::unique_ptr<pqxx::work>& dbInstance) : _dbInstance(dbInstance) {}
    
    Country countryById(size_t id) const override {
        Country country;
        try {
            pqxx::result result(_dbInstance -> exec("SELECT id, name FROM countries")); 
            
            if (result.size() > 1) {
                throw std::logic_error("could not be more then one city with same id");
            }
            
            if (result.empty() ) {
                throw StoreException(StoreException::EMPTY_RESPONSE);
            }
            
            for (auto row: result) {
                country.id = row["id"].as<size_t>();
                country.name = row["name"].c_str();
            }
        } catch (pqxx::sql_error& e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query was: " << e.query() << std::endl;
            std::rethrow_exception(std::current_exception());
        } catch (...) {
            std::rethrow_exception(std::current_exception());
        }
        return country;
    }
    
private:
    std::unique_ptr<pqxx::work>& _dbInstance;
    
};

#endif
