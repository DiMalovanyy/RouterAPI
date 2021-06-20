cmake_minimum_required(VERSION 3.5)

Project(RestAPI LANGUAGES C CXX VERSION 0.0.1)

set(BINARY ${CMAKE_PROJECT_NAME}_exe)

#find boost
find_package(Boost REQUIRED)
if ( NOT ${BOOST_FOUND})
	message(FATAL_ERROR "Boost librarie was not found")
else()
	message(STATUS "Boost librarie version ${Boost_VERSION} was found")
	include_directories(${Boost_INCLUDE_DIRS})
endif()


#build libraries
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/libpqxx)

include_directories(
	server
	)

set(SOURCES 
	main.cpp
	server/restapi.cpp
	)
set(HEADERS 
	server/restapi.h
	)

#copy toml config file to directory where binary file exec from
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/apiConfig.toml ${CMAKE_CURRENT_BINARY_DIR}/apiConfig.toml COPYONLY)


add_executable(${BINARY} ${SOURCES} ${HEADERS})

#link libraries
target_link_libraries(${BINARY} pqxx)
target_link_libraries(${BINARY} ${Boost_LIBRARIES})



set_target_properties(${BINARY} PROPERTIES
			CXX_STANDARD 17
			CXX_STANDARD_REQUIRED ON
			)
		
#libs include dirs		
target_include_directories(${BINARY} PRIVATE ${CMAKE_SOURCE_DIR}/libs/tomlplusplus/include)
target_include_directories(${BINARY} PRIVATE ${CMAKE_SOURCE_DIR}/libs/spdlog/include)
target_include_directories(${BINARY} PRIVATE ${CMAKE_SOURCE_DIR}/libs/libpqxx/include)
