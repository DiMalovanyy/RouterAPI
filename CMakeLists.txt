cmake_minimum_required(VERSION 3.5)

Project(RestAPI LANGUAGES C CXX VERSION 0.0.1)

set(BINARY ${CMAKE_PROJECT_NAME}_exe)


set(SOURCES 
	main.cpp
	)
set(HEADERS 
	)

add_executable(${BINARY} ${SOURCES} ${HEADERS})
set_target_properties(${BINARY} PROPERTIES
			CXX_STANDARD 17
			CXX_STANDARD_REQUIRED ON
			)
target_include_directories(${BINARY} PRIVATE ${CMAKE_SOURCE_DIR}/libs/tomlplusplus/include)
