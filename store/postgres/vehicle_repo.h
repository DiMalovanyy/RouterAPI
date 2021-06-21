#ifndef POSTGRES_VEHICLE_REPO_H
#define POSTGRES_VEHICLE_REPO_H

#include "repos.h"

#include <memory>
#include <pqxx/pqxx>

class PostgresVehicleRepo final: public VehicleRepo {
public:
    
    PostgresVehicleRepo(std::unique_ptr<pqxx::work>& dbInstance) : _dbInstance(dbInstance) {}
    
    Vehicle vehicleById(size_t id) const override {
        Vehicle vehicle;
        try {
            pqxx::result result(_dbInstance -> exec("SELECT id, name FROM vehicle WHERE id = " + _dbInstance -> quote(id)));
            if (result.size() > 1) {
                throw std::logic_error("could not be more then one city with same id");
            }
            
            if (result.empty() ) {
                throw StoreException(StoreException::EMPTY_RESPONSE);
            }
            
            for (auto row: result) {
                vehicle.id = row["id"].as<size_t>();
                vehicle.name = row["name"].c_str();
            }
        } catch (pqxx::sql_error& e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query was: " << e.query() << std::endl;
            std::rethrow_exception(std::current_exception());
        } catch (...) {
            std::rethrow_exception(std::current_exception());
        }
        return vehicle;
    }
    
private:
    std::unique_ptr<pqxx::work>& _dbInstance;
};

#endif
