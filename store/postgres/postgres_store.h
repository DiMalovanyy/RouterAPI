#ifndef POSTGRES_STORE_H
#define POSTGRES_STORE_H


#include <memory>
#include <pqxx/pqxx>

#include "store.h"

#include "city_repo.h"
#include "country_repo.h"
#include "route_repo.h"
#include "user_repo.h"
#include "vehicle_repo.h"

class PostgresStore final: public Store {
public:
    
    PostgresStore(const std::string& databaseConnectionURL);
    
    std::unique_ptr<CityRepo>& City()override ;
    std::unique_ptr<CountryRepo>& Country() override;
    std::unique_ptr<UserRepo> & User()  override;
    std::unique_ptr<VehicleRepo> & Vehicle()  override;
    std::unique_ptr<RouteRepo>& Route() override;

    
private:
    //PostgresDB instance
    std::unique_ptr<pqxx::work> _databaseInstance;
    
    
    std::unique_ptr<CityRepo> _cityRepo;
    std::unique_ptr<UserRepo> _userRepo;
    std::unique_ptr<CountryRepo> _countryRepo;
    std::unique_ptr<VehicleRepo> _vehicleRepo;
    std::unique_ptr<RouteRepo> _routeRepo;
};


#endif
