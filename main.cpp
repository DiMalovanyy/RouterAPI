
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


void initLoggers() {
    //Stdcout logger
    auto consoleLogger = spdlog::stdout_color_mt("console");
    spdlog::get("console") -> info("Logger \"{0}\" init successfully", "console");
    
    //File logger
    //TODO: add file logger
}



struct APIParams {
    const char* host;
    const char* port;
};

void parseTomlConfig( const char* confiPath, bool logParams = false) {
    toml::table table;
    try {
        table = toml::parse_file( confiPath );
    } catch (const toml::parse_error& err) {
        std::cerr << "Some errors while parsing toml occured" << std::endl;
        exit(EXIT_FAILURE);
    }
    spdlog::get("console") -> info("Toml config was parsed successfully from the path \"{0}\"", confiPath);
    if ( logParams ) {
        spdlog::get("console") -> info("Toml parsed parms");
        for (int i = 0; i < table.size(); ++i) {
            //TODO: params info
//            spdlog::get("console") -> info("\t{0}: {1}", table.)
        }
        
    }
    
}



int main(int argc, char ** argv) {
    initLoggers();
    parseTomlConfig("./apiConfig.toml");
    
	return 0;
}
