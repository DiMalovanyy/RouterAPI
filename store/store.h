#ifndef STORE_H
#define STORE_H

#include "repos.h"

class Store {
public:
    virtual CityRepo City() const = 0;
    virtual CountryRepo Country() const = 0;
    virtual UserRepo User() const = 0;
    virtual VehicleRepo Vehicle() const = 0;
    virtual RouteRepo Route() const = 0;
};

#endif
