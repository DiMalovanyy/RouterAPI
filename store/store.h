#ifndef STORE_H
#define STORE_H

#include <memory>

#include "repos.h"

class Store {
public:
    virtual std::unique_ptr<CityRepo>& City()  = 0;
    virtual std::unique_ptr<CountryRepo>& Country()  = 0;
    virtual std::unique_ptr<UserRepo>& User()  = 0;
    virtual std::unique_ptr<VehicleRepo>& Vehicle()  = 0;
    virtual std::unique_ptr<RouteRepo>& Route()  = 0;
};

#endif
