#include "webSocketSession.h"


WebSocketSession::WebSocketSession( boost::asio::ip::tcp::socket&& socket) : _socketStream(std::move(socket)) {}


void WebSocketSession::onAccept(boost::beast::error_code error_code) {
    if(error_code) {
        fail(error_code, "Accept"); return;
    }
    doRead();
}

void WebSocketSession::doRead() {
    //Read message into our buffer
    _socketStream.async_read(
                _dynamicBuffer,
                boost::beast::bind_front_handler(
                    &WebSocketSession::onRead,
                    shared_from_this()));
}


void WebSocketSession::onRead(boost::beast::error_code error_code, [[maybe_unused]] size_t bytes_transfered ) {
    // This indicates that the websocket_session was closed
    if(error_code == boost::beast::websocket::error::closed) {
        return;
    } else if(error_code) {
        fail(error_code, "read");
    }
    
    // Echo the message
    _socketStream.text(_socketStream.got_text());
    _socketStream.async_write(
                _dynamicBuffer.data(),
                boost::beast::bind_front_handler(
                    &WebSocketSession::onWrite,
                    shared_from_this()));
    
}

void WebSocketSession::onWrite(boost::beast::error_code error_code, [[maybe_unused]] size_t bytes_transfered) {
    if(error_code) {
        fail(error_code, "write");
    }
    _dynamicBuffer.consume(_dynamicBuffer.size()); // Clear the buffer
    doRead(); // Do another read
}
