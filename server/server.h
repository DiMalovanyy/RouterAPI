#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <thread>

#include "precompiled.h"

#include "acceptor.h"
#include "serverUtility.h"

#include "router.h"
#include "handler.h"

#include "store/postgres/postgres_store.h"
#include "serverUtility.h"



class Server {
public:
    
    Server(const APIParams &params);
    void Run();

private:
    
    
    void ConfigureRouter();
    void ConfigureDataBase();
    
    APIParams _params;
    
    std::unique_ptr<PostgresStore>;
    std::unique_ptr<HttpRouter> _router;
    
    boost::asio::io_context _ioc;
    std::vector<std::unique_ptr<std::thread>> _thread_pool;
    std::shared_ptr<Acceptor> _acceptor;
};


#endif
