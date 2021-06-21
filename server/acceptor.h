#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "precompiled.h"

#include "serverUtility.h"
#include "httpSession.h"

//Acceptor accept incoming connectiond and initiate a session
class Acceptor: public std::enable_shared_from_this<Acceptor> {
public:
    
    Acceptor(boost::asio::io_context& ioc, const size_t port_num, const std::unique_ptr<HttpRouter>& router);
    //Start incoming connections
    void Run();
    
private:
    
    
    void doAccept();
    void onAccept(boost::beast::error_code error_code, boost::asio::ip::tcp::socket socket);
    
    boost::asio::io_context &_ioc;
    boost::asio::ip::tcp::acceptor _acceptor;
    
    const std::unique_ptr<HttpRouter>& _router;
};

#endif
