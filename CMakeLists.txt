cmake_minimum_required(VERSION 3.16)

Project(RestAPI LANGUAGES C CXX VERSION 0.0.1)

set(BINARY ${CMAKE_PROJECT_NAME}_exe)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -w")

#find boost
find_package(Boost REQUIRED)
if ( NOT ${BOOST_FOUND})
	message(FATAL_ERROR "Boost librarie was not found")
else()
	message(STATUS "Boost librarie version ${Boost_VERSION} was found")
	include_directories(${Boost_INCLUDE_DIRS})
endif()

#find_package( PQXX )
#if (NOT ${PQXX_FOUND})
#	add_subdirectory(${CMAKE_SOURCE_DIR}/libs/libpqxx)
#	include_directories( ${CMAKE_SOURCE_DIR}/libs/libpqxx/include)
#else()
#	include_directories( ${PQXX_INCLUDE_DIRECTORIES} )
#endif()

include_directories(
	${CMAKE_SOURCE_DIR}
	${CMAKE_BINARY_DIR}
	server
	router
	Utils
	)

set(SOURCES 
	main.cpp
	server/server.cpp
	server/acceptor.cpp
	server/httpSession.cpp
	server/webSocketSession.cpp
	server/serverUtility.cpp
	server/requestProcessor.cpp
	router/router.cpp
	router/handler.cpp
	)
set(HEADERS 
	server/server.h
	server/acceptor.h
	server/httpSession.h
	server/webSocketSession.h
	server/serverUtility.h
	server/requestProcessor.h
	router/router.h
	router/handler.h
	router/httpUtils.h
	)

#copy toml config file to directory where binary file exec from
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/apiConfig.toml ${CMAKE_CURRENT_BINARY_DIR}/apiConfig.toml COPYONLY)


add_executable(${BINARY} ${SOURCES} ${HEADERS})
target_precompile_headers(${BINARY} PRIVATE precompiled.h)

#link libraries
#if (NOT ${PQXX_FOUND})
#	target_link_libraries(${BINARY} pqxx)
#else()
#	target_link_libraries(${BINARY} ${PQXX_LIBRARIES})
#endif()

target_link_libraries(${BINARY} ${Boost_LIBRARIES})

if(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
	target_link_libraries(${BINARY} pthread)
endif() 

set_target_properties(${BINARY} PROPERTIES
			CXX_STANDARD 17
			CXX_STANDARD_REQUIRED ON
			)
		
#libs include dirs		
target_include_directories(${BINARY} PRIVATE ${CMAKE_SOURCE_DIR}/libs/tomlplusplus/include)
target_include_directories(${BINARY} PRIVATE ${CMAKE_SOURCE_DIR}/libs/spdlog/include)
target_include_directories(${BINARY} PRIVATE ${CMAKE_SOURCE_DIR}/libs/libpqxx/include)
target_include_directories(${BINARY} PRIVATE ${CMAKE_SOURCE_DIR}/libs/rapidjson)
