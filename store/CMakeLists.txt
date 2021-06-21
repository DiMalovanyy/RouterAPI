cmake_minimum_required(VERSION 3.16)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

find_package(PostgreSQL REQUIRED)
find_package(PQXX REQUIRED)
if(NOT ${PQXX_FOUND})
	message( "pqxx dows not found")
endif()

include_directories(${CMAKE_SOURCE_DIR}/../model)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/postgres)

set( HEADERS
	repos.h
	store.h
	errors.h
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
	errors.cpp
    postgres/postgres_store.cpp
    postgres/user_repo.cpp
    postgres/vehicle_repo.cpp
    postgres/city_repo.cpp
    postgres/country_repo.cpp
    postgres/route_repo.cpp
	)

add_executable(StoreTest ${SOURCES} ${HEADERS} main.cpp)
set_target_properties(StoreTest PROPERTIES
                CXX_STANDARD 17
                CXX_STANDARD_REQUIRED ON
)
target_include_directories(StoreTest PRIVATE ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(StoreTest PRIVATE ${PostgreSQL_LIBRARIES})
target_include_directories(StoreTest PRIVATE ${PQXX_INCLUDE_DIR})
target_link_libraries(StoreTest PRIVATE ${PQXX_LIBRARIES})
