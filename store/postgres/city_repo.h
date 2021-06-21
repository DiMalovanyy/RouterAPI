#ifndef POSTGRES_CITY_REPO_H
#define POSTGRES_CITY_REPO_H

#include "repos.h"


class PostgresCityRepo final : public CityRepo {
public:
    
    City cityById(size_t) const override {
        
        return {};
    }
    
    
};

#endif
