
#include "postgres_store.h"

PostgresStore::PostgresStore() {
    //Constructor for db instance
}

std::unique_ptr<CityRepo> & PostgresStore::City() {
    if (_cityRepo != nullptr) {
        return _cityRepo;
    }
    
    _cityRepo = std::make_unique<PostgresCityRepo>();
    return _cityRepo;
}

std::unique_ptr<CountryRepo>& PostgresStore::Country() {
    if (_countryRepo != nullptr) {
        return _countryRepo;
    }
    
    _countryRepo = std::make_unique<PostgresCountryRepo>();
    return _countryRepo;
}

std::unique_ptr<UserRepo> & PostgresStore::User()  {
    if (_userRepo != nullptr) {
        return _userRepo;
    }
    
    _userRepo = std::make_unique<PostgresUserRepo>();
    return _userRepo;
}

std::unique_ptr<VehicleRepo> & PostgresStore::Vehicle() {
    if (_vehicleRepo != nullptr) {
        return _vehicleRepo;
    }
    
    _vehicleRepo = std::make_unique<PostgresVehicleRepo>();
    return _vehicleRepo;
}

std::unique_ptr<RouteRepo>& PostgresStore::Route() {
    if (_routeRepo != nullptr) {
        return _routeRepo;
    }
    
    _routeRepo = std::make_unique<PostgresRouteRepo>();
    return _routeRepo;
}
