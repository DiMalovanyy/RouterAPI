
#include <iostream>

//C libs
#include <stdio.h>
#include <stdlib.h>

#include <toml++/toml.h>



struct APIParams {
    const char* host;
    const char* port;
};

void parseTomlConfig( const char* confiPath ) {
    toml::table table;
    try {
        table = toml::parse_file( confiPath );
    } catch (const toml::parse_error& err) {
        std::cerr << "Some errors while parsing toml occured" << std::endl;
        exit(EXIT_FAILURE);
    }
}



int main(int argc, char ** argv) {


	puts("Hello Api\n");
	return 0;
}
