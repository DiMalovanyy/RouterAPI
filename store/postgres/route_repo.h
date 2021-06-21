#ifndef POSTGRES_ROUTE_REPO_H
#define POSTGRES_ROUTE_REPO_H

#include "repos.h"

#include <memory>
#include <pqxx/pqxx>

class PostgresRouteRepo final : public RouteRepo {
public:
    
    PostgresRouteRepo(std::unique_ptr<pqxx::work>& dbInstance) : _dbInstance(dbInstance) {}
    
    Route routeById(size_t id) const override {
        Route route;
        try {
            pqxx::result result(_dbInstance -> exec("SELECT id, sourceFromId, destinationId, passangerId, vehicleId FROM routes WHERE id = " + _dbInstance -> quote(id)));
            if (result.size() > 1) {
                throw std::logic_error("could not be more then one city with same id");
            }
            
            if (result.empty() ) {
                throw StoreException(StoreException::EMPTY_RESPONSE);
            }
            
            for (auto row: result) {
                route.id = row["id"].as<size_t>();
                route.citySourceId = row["sourceFromId"].as<size_t>();
                route.cityDestinationId = row["destinationId"].as<size_t>();
                route.passagerId = row["passangerId"].as<size_t>();
                route.vehicleId = row["vehicleId"].as<size_t>();
            }
        } catch (pqxx::sql_error& e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query was: " << e.query() << std::endl;
            std::rethrow_exception(std::current_exception());
        } catch (...) {
            std::rethrow_exception(std::current_exception());
        }
        return route;
    }
    
private:
    std::unique_ptr<pqxx::work>& _dbInstance;
    
};

#endif
