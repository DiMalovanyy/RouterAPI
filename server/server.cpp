#include <server.h>

Server::Server(const short thread_pool_size) : _ioc(thread_pool_size), _thread_pool_size(thread_pool_size) {
    assert(thread_pool_size > 0);
    _thread_pool.reserve(thread_pool_size - 1);
    
    ConfigureRouter();
}


void Server::Run(const short port_num) {
    _acceptor.reset(new Acceptor(_ioc, port_num, _router));
    _acceptor -> Run();
    
    
    // Capture SIGINT and SIGTERM to perform a clean shutdown
    boost::asio::signal_set signals(_ioc, SIGINT, SIGTERM);
    signals.async_wait(
        [&](boost::beast::error_code const&, int) {
            _ioc.stop();
        });
    
    for (short thread_index = _thread_pool_size - 1; thread_index > 0; --thread_index) {
        _thread_pool.emplace_back(new std::thread([_ioc = &_ioc](){
            _ioc -> run();
        }));
    }
    _ioc.run();
    
    // (If we get here, it means we got a SIGINT or SIGTERM)
    
    // Block until all the threads exit
    for (const auto& thread : _thread_pool) {
        thread -> join();
    }
    
}


void Server::ConfigureRouter() {
    
    _router = std::make_unique<HttpRouter>();
    //Debug only
    _router -> AddHandler("/hello/", std::make_unique<SayHelloHandler>());
    
}
