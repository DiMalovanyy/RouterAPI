
#ifndef WEB_SOCKET_SESSION_H
#define WEB_SOCKET_SESSION_H

#include <utility>
#include <memory>



#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include "serverUtility.h"


// Echoes back all received WebSocket messages
class WebSocketSession : public std::enable_shared_from_this<WebSocketSession> {
public:
    
    //Take ownership of the socket
    explicit WebSocketSession( boost::asio::ip::tcp::socket&& socket );
    
    //Start the async accept operation
    template <typename Body, typename Allocator>
    void doAccept(boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>> request);
    
private:
    
    void onAccept(boost::beast::error_code error_code);
    
    void doRead();
    
    void onRead(boost::beast::error_code error_code, [[maybe_unused]] size_t bytes_transfered );
    
    void onWrite(boost::beast::error_code error_code, [[maybe_unused]] size_t bytes_transfered);
    
    boost::beast::websocket::stream<boost::beast::tcp_stream> _socketStream;
    boost::beast::flat_buffer _dynamicBuffer;
};


template <typename Body, typename Allocator>
void WebSocketSession::doAccept(boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>> request) {
    // Set suggested timeout settings for the websocket
    _socketStream.set_option
        ( boost::beast::websocket::stream_base::timeout::suggested( boost::beast::role_type::server ) );
    
    // Set a decorator to change the Server of the handshake
    _socketStream.set_option(boost::beast::websocket::stream_base::decorator(
        [](boost::beast::websocket::response_type& res) {
            res.set(boost::beast::http::field::server, "Hello from server");
        }));
    
    _socketStream.async_accept( request,
                                boost::beast::bind_front_handler( &WebSocketSession::onAccept, shared_from_this() ) );
}

#endif
