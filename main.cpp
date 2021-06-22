
#include <iostream>

//C libs
#include <stdio.h>
#include <stdlib.h>



//Other libs

//Toml
#include <toml++/toml.h>
//Logger
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
//Postgresql
// #include <pqxx/pqxx>



//Server
#include "server/server.h"
#include "server/serverUtility.h"


void initLoggers() {
    //Stdcout logger
    auto consoleLogger = spdlog::stdout_color_mt("console");
    spdlog::get("console") -> info("Logger \"{0}\" init successfully", "console");

    //File logger
    //TODO: add file logger
}

APIParams parseTomlConfig( const char* confiPath, bool logParams = false) {
    toml::table table;
    try {
        table = toml::parse_file( confiPath );
    } catch (const toml::parse_error& err) {
        std::cerr << "Some errors while parsing toml occured" << std::endl;
        exit(EXIT_FAILURE);
    }
    spdlog::get("console") -> info("Toml config was parsed successfully from the path \"{0}\"", confiPath);

    APIParams params;
    params.port = table["port"].value_or("1433");
    params.host = table["host"].value_or("127.0.0.1");
    params.databaseConnectionURL =  table["database"].value_or("none");
    params.threadPoolSize = std::thread::hardware_concurrency();

    if ( logParams ) {
        spdlog::get("console") -> info("RestApi address: {0}:{1}", params.host, params.port);
        spdlog::get("console") -> info("Database connection url: {}", params.databaseConnectionURL);
    }

    return params;
}


int main(int argc, char ** argv) {
    initLoggers();
    auto params = parseTomlConfig("./apiConfig.toml", true);


    Server httpServer(params);
    httpServer.Run();


	return 0;
}
