cmake_minimum_required(VERSION 3.5)

Project(RestAPI LANGUAGES C CXX VERSION 0.0.1)

set(BINARY ${CMAKE_PROJECT_NAME}_exe)

set(SOURCES 
	main.cpp
	)
set(HEADERS 
	)

add_executable(${BINARY} ${SOURCES} ${HEADERS})
