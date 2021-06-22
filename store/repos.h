#ifndef REPOS_H
#define REPOS_H

#include <vector>
#include <string>


#include "city.h"
#include "country.h"
#include "user.h"
#include "vehicle.h"
#include "route.h"

class CityRepo {
public:
    virtual City cityById(size_t) const = 0;
    
    virtual ~CityRepo() {}
};

class CountryRepo {
public:
    virtual Country countryById(size_t) const = 0;
    
    virtual ~CountryRepo() {}
};

class UserRepo {
public:
    virtual User userById(size_t) const = 0;
    virtual std::vector<User> getAllUsers() const = 0;
    virtual int addUser(const std::string& ) = 0;
    
    virtual ~UserRepo() {}
};

class VehicleRepo {
public:
    virtual Vehicle vehicleById(size_t) const = 0;
    
    virtual ~VehicleRepo() {}
};

class RouteRepo {
public:
    virtual Route routeById(size_t) const = 0;
    
    virtual ~RouteRepo() {}
};


#endif

