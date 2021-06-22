#ifndef POSTGRES_USER_REPO_H
#define POSTGRES_USER_REPO_H

#include "repos.h"

#include <memory>
#include <pqxx/pqxx>

class PostgresUserRepo final: public UserRepo {
public:
    
    PostgresUserRepo(std::unique_ptr<pqxx::work>& dbInstance) : _dbInstance(dbInstance) {}
    
    
    User userById(size_t id) const override {
        User user;
        try {
            pqxx::result result(_dbInstance -> exec("SELECT id, name FROM users WHERE id = " + _dbInstance -> quote(id)));
            if (result.size() > 1) {
                throw std::logic_error("could not be more then one city with same id");
            }
            
            if (result.empty() ) {
                throw StoreException(StoreException::EMPTY_RESPONSE);
            }
            
            for (auto row: result) {
                user.id = row["id"].as<size_t>();
                user.name = row["name"].c_str();
            }
        } catch (pqxx::sql_error& e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query was: " << e.query() << std::endl;
            std::rethrow_exception(std::current_exception());
        } catch (...) {
            std::rethrow_exception(std::current_exception());
        }
        return user;
    }
    
    std::vector<User> getAllUsers() const override {
        std::vector<User> users;
        try {
            pqxx::result result(_dbInstance -> exec("Select id, name FROM users"));
            
            for (auto row: result) {
                users.push_back(User{row["id"].as<size_t>(), row["name"].c_str()});
            }
            
        } catch (pqxx::sql_error& e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query was: " << e.query() << std::endl;
            std::rethrow_exception(std::current_exception());
        } catch (...) {
            std::rethrow_exception(std::current_exception());
        }
        return users;
    }
    
    void addUser(const User& user) const override {
        
        try {
            
            
            
            
        } catch (pqxx::sql_error& e) {
            
            
        } catch (pqxx::sql_error& e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            std::cerr << "Query was: " << e.query() << std::endl;
            std::rethrow_exception(std::current_exception());
        } catch (...) {
            std::rethrow_exception(std::current_exception());
        }
        
    }
    
private:
    std::unique_ptr<pqxx::work>& _dbInstance;
    
};


#endif
