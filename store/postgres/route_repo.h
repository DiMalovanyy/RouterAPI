#ifndef POSTGRES_ROUTE_REPO_H
#define POSTGRES_ROUTE_REPO_H

#include "repos.h"

class PostgresRouteRepo final : public RouteRepo {
public:
    
    Route routeById(size_t) const override {
        
        return {};
    }
    
};

#endif
