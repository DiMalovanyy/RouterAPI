cmake_minimum_required(VERSION 3.16)

set(HEADERS
	city.h
	country.h
	route.h
	vehicle.h
	)

set(SOURCES
	city.cpp
	country.cpp
	route.cpp
	vehicle.cpp
	)

add_executable(TestModel ${SOURCES} ${HEADERS} main.cpp)
