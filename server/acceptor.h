#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <utility>
#include <memory>

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include "serverUtility.h"
#include "httpSession.h"

//Acceptor accept incoming connectiond and initiate a session
class Acceptor: public std::enable_shared_from_this<Acceptor> {
public:
    
    Acceptor(boost::asio::io_context& ioc, const size_t port_num);
    //Start incoming connections
    void Run();
    
private:
    
    void doAccept();
    void onAccept(boost::beast::error_code error_code, boost::asio::ip::tcp::socket socket);
    
    boost::asio::io_context &_ioc;
    boost::asio::ip::tcp::acceptor _acceptor;
};

#endif
