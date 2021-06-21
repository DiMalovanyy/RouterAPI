#ifndef POSTGRES_COUNTRY_REPO_H
#define POSTGRES_COUNTRY_REPO_H

#include "repos.h"

class PostgresCountryRepo final: public CountryRepo {
public:
    
    Country countryById(size_t) const override {
        
        return {};
    }
    
};

#endif
