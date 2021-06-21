cmake_minimum_required(VERSION 3.16)

set(HEADERS
	city.h
	country.h
	route.h
	vehicle.h
    user.h
    precompiled.h
	)

set(SOURCES
	city.cpp
	country.cpp
	route.cpp
	vehicle.cpp
    user.cpp
	)

add_executable(TestModel ${SOURCES} ${HEADERS} main.cpp)
target_precompile_headers(TestModel PUBLIC precompiled.h)
