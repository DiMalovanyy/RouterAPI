#ifndef SERVER_H
#define SERVER_H

#include <utility>
#include <vector>
#include <memory>
#include <thread>

#include <boost/asio.hpp>

#include "acceptor.h"
#include "serverUtility.h"


class Server {
public:
    
    Server(const short thread_pool_size);
    void Run(const short port_num);

private:
    boost::asio::io_context _ioc;
    const short _thread_pool_size;
    std::vector<std::unique_ptr<std::thread>> _thread_pool;
    std::shared_ptr<Acceptor> _acceptor;
};


#endif
