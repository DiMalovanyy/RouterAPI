
#include "postgres_store.h"

#include <exception>



PostgresStore::PostgresStore(const std::string& databaseConnectionURL) {
    //Constructor for db instance
    pqxx::connection connection(databaseConnectionURL);
    _databaseInstance = std::make_unique<pqxx::work>(connection);
}

std::unique_ptr<CityRepo> & PostgresStore::City() {
    if (_cityRepo != nullptr) {
        return _cityRepo;
    }
    
    _cityRepo = std::make_unique<PostgresCityRepo>(_databaseInstance);
    return _cityRepo;
}

std::unique_ptr<CountryRepo>& PostgresStore::Country() {
    if (_countryRepo != nullptr) {
        return _countryRepo;
    }
    
    _countryRepo = std::make_unique<PostgresCountryRepo>(_databaseInstance);
    return _countryRepo;
}

std::unique_ptr<UserRepo> & PostgresStore::User()  {
    if (_userRepo != nullptr) {
        return _userRepo;
    }
    
    _userRepo = std::make_unique<PostgresUserRepo>(_databaseInstance);
    return _userRepo;
}

std::unique_ptr<VehicleRepo> & PostgresStore::Vehicle() {
    if (_vehicleRepo != nullptr) {
        return _vehicleRepo;
    }
    
    _vehicleRepo = std::make_unique<PostgresVehicleRepo>(_databaseInstance);
    return _vehicleRepo;
}

std::unique_ptr<RouteRepo>& PostgresStore::Route() {
    if (_routeRepo != nullptr) {
        return _routeRepo;
    }
    
    _routeRepo = std::make_unique<PostgresRouteRepo>(_databaseInstance);
    return _routeRepo;
}
