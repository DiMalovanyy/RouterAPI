cmake_minimum_required(VERSION 3.16)


set( HEADERS
	repos.h
	store.h
	)

set( SOURCES
	repos.cpp
	store.cpp
	)

add_executable(StoreTest ${SOURCES} ${HEADERS} main.cpp)
