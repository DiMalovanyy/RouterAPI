
#include <acceptor.h>

#include <spdlog/spdlog.h>



Acceptor::Acceptor(boost::asio::io_context& ioc, const size_t port_num, const std::unique_ptr<HttpRouter>& router)
: _ioc(ioc), _acceptor(boost::asio::make_strand(ioc)), _router(router) {
    boost::beast::error_code error_code;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port_num);
    
    _acceptor.open(endpoint.protocol(), error_code);
    if(error_code) {
        fail(error_code, "open"); return;
    }
    _acceptor.set_option(boost::asio::socket_base::reuse_address(true), error_code);
    if(error_code) {
        fail(error_code, "set address"); return;
    }
    _acceptor.bind(endpoint, error_code);
    if(error_code) {
        fail(error_code, "bind"); return;
    }
    //Start listening for connections
    _acceptor.listen(boost::asio::socket_base::max_listen_connections, error_code);
    spdlog::get("console") -> info("Acceptor start listening on port {} ", port_num);
    if (error_code) {
        fail(error_code, "listen");
    }
}

void Acceptor::Run() {
    spdlog::get("console") -> info("Acceptor start acceptions...");
    doAccept();
}


void Acceptor::doAccept() {
    _acceptor.async_accept(
                           boost::asio::make_strand(_ioc),
                           boost::beast::bind_front_handler(
            &Acceptor::onAccept,
            shared_from_this()));
}

void Acceptor::onAccept(boost::beast::error_code error_code, boost::asio::ip::tcp::socket socket) {
    if(error_code) {
        fail(error_code, "accept");
    } else {
        spdlog::get("console") -> info("Acceptor accept new connection");
        // Create the http session and run it
        std::make_shared<HttpSession>(
            std::move(socket), _router)->Run();
    }
    // Accept another connection
    doAccept();
}

