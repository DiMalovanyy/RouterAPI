

#include <stdio.h>

#include "postgres/postgres_store.h"

int main(int argc, char ** argv) {
    //Tests
    
//    pqxx::connection c{"postgres://postgres:12345@localhost:5434/univerDB2?sslmode=disable"};
//    pqxx::work txn{c};
//
//    pqxx::result r{txn.exec("SELECT id, name FROM users")};
//    for (auto row: r) {
//        std::cout << "Id: " << row["id"].as<size_t>() << std::endl;
//        std::cout << "Name: " << row["name"].c_str() << std::endl << std::endl;
//    }
    
    
    PostgresStore store("postgres://postgres:12345@localhost:5434/univerDB2?sslmode=disable");

    try {
        Country c = store.Country()-> countryById(0);
        User u = store.User() -> userById(0);
        
        std::cout << "Id: " << c.id << std::endl;
        std::cout << "Name: " << c.name << std::endl;
    } catch (StoreException& e) {
        std::cout << "Error description: " << e.what() << std::endl;
    } catch (std::exception& e) {
        std::cout << "Undefined exception: " << e.what() << std::endl;
    }

    
    
    return 0;
}
