#ifndef POSTGRES_VEHICLE_REPO_H
#define POSTGRES_VEHICLE_REPO_H

#include "repos.h"

class PostgresVehicleRepo final: public VehicleRepo {
public:
    
    
    Vehicle vehicleById(size_t) const override {
        
        return {};
    }
    
};

#endif
