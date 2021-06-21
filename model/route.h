#ifndef ROUTE_H
#define ROUTE_H

#include "precompiled.h"

struct Route {
    size_t id;
    
    size_t citySourceId;
    size_t cityDestinationId;
    
    size_t passagerId;
    size_t vehicleId;
};

#endif
