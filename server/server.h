#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <thread>

#include "precompiled.h"

#include "acceptor.h"
#include "serverUtility.h"

#include "router.h"
#include "handler.h"



class Server {
public:
    
    Server(const short thread_pool_size);
    void Run(const short port_num);

private:
    
    
    void ConfigureRouter();
    
    std::unique_ptr<HttpRouter> _router;
    
    boost::asio::io_context _ioc;
    const short _thread_pool_size;
    std::vector<std::unique_ptr<std::thread>> _thread_pool;
    std::shared_ptr<Acceptor> _acceptor;
};


#endif
