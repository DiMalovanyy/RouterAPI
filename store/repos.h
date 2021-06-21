#ifndef REPOS_H
#define REPOS_H

#include <memory>


#include "city.h"
#include "country.h"
#include "user.h"
#include "vehicle.h"
#include "route.h"

class CityRepo {
public:
    virtual std::unique_ptr<City>& cityById(size_t) const = 0;
};

class CountryRepo {
public:
    virtual std::unique_ptr<Country>& countryById(size_t) const = 0;
};

class UserRepo {
public:
    virtual std::unique_ptr<User>& userById(size_t) const = 0;
};

class VehicleRepo {
public:
    virtual std::unique_ptr<Vehicle>& vehicleById(size_t) const = 0;
};

class RouteRepo {
public:
    virtual std::unique_ptr<Route>& routeById(size_t) const = 0;
    
};


#endif

