#ifndef POSTGRES_CITY_REPO_H
#define POSTGRES_CITY_REPO_H

#include "repos.h"
#include "errors.h"



#include <iostream>
#include <memory>
#include <pqxx/pqxx>

class PostgresCityRepo final : public CityRepo {
public:
    
    PostgresCityRepo(std::unique_ptr<pqxx::work>& dbInstance) : _dbInstance(dbInstance) {}
    
    City cityById(size_t id) const override {
        City city;
        try {
            pqxx::result result(_dbInstance -> exec("SELECT id, name, countryId FROM cities WHERE id = " + _dbInstance -> quote(id)));
            if (result.size() > 1) {
                throw std::logic_error("could not be more then one city with same id");
            }
            
            if (result.empty() ) {
                throw StoreException(StoreException::EMPTY_RESPONSE);
            }
            
            for (auto row: result) {
                city.id = row["id"].as<size_t>();
                city.name = row["name"].c_str();
                city.countryId = row["countryId"].as<size_t>();
            }
        } catch (pqxx::sql_error& e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query was: " << e.query() << std::endl;
            std::rethrow_exception(std::current_exception());
        } catch (...) {
            std::rethrow_exception(std::current_exception());
        }
        
        return city;
    }
    
private:
    std::unique_ptr<pqxx::work>& _dbInstance;
};

#endif
