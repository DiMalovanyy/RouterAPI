#ifndef POSTGRES_VEHICLE_REPO_H
#define POSTGRES_VEHICLE_REPO_H

#include "repos.h"

#include <memory>
#include <pqxx/pqxx>

class PostgresVehicleRepo final: public VehicleRepo {
public:
    
    PostgresVehicleRepo(std::unique_ptr<pqxx::work>& dbInstance) : _dbInstance(dbInstance) {}
    
    Vehicle vehicleById(size_t) const override {
        
        return {};
    }
    
private:
    std::unique_ptr<pqxx::work>& _dbInstance;
};

#endif
