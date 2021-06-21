cmake_minimum_required(VERSION 3.16)


include_directories(${CMAKE_SOURCE_DIR}/../model)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/postgres)
set( HEADERS
	repos.h
	store.h
    postgres/postgres_store.h
    postgres/user_repo.h
    postgres/vehicle_repo.h
    postgres/city_repo.h
    postgres/country_repo.h
    postgres/route_repo.h
	)

set( SOURCES
	repos.cpp
	store.cpp
    postgres/postgres_store.cpp
    postgres/user_repo.cpp
    postgres/vehicle_repo.cpp
    postgres/city_repo.cpp
    postgres/country_repo.cpp
    postgres/route_repo.cpp
	)

add_executable(StoreTest ${SOURCES} ${HEADERS} main.cpp)
