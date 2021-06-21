#ifndef POSTGRES_ROUTE_REPO_H
#define POSTGRES_ROUTE_REPO_H

#include "repos.h"

#include <memory>
#include <pqxx/pqxx>

class PostgresRouteRepo final : public RouteRepo {
public:
    
    PostgresRouteRepo(std::unique_ptr<pqxx::work>& dbInstance) : _dbInstance(dbInstance) {}
    
    Route routeById(size_t) const override {
        
        return {};
    }
    
private:
    std::unique_ptr<pqxx::work>& _dbInstance;
    
};

#endif
