
#include "httpSession.h"



HttpSession::HttpSession(boost::asio::ip::tcp::socket&& socket)
    : _socketStream(std::move(socket)), _queue(Queue(*this)) {}

void HttpSession::Run() {
    doRead();
}

void HttpSession::doRead() {
    _parser.emplace();  //Construct new parser for each message
    _parser->body_limit(10000);  // Apply a reasonable limit to the allowed size of the body in bytes to prevent abuse.
    _socketStream.expires_after(std::chrono::seconds(30));  //Set the timeouts
    
    // Read a request using the parser-oriented interface
    boost::beast::http::async_read( _socketStream, _dynamicBuffer, *_parser,
                            boost::beast::bind_front_handler(&HttpSession::onRead, shared_from_this()));
}

void HttpSession::onRead(boost::beast::error_code error_code, [[maybe_unused]] size_t bytes_transfered) {
    if(error_code == boost::beast::http::error::end_of_stream) {  // This means they closed the connection
        return doClose();
    } else if(error_code) { //Other fail
        return fail(error_code, "read");
    }
    
    // See if it is a WebSocket Upgrade
    if (boost::beast::websocket::is_upgrade(_parser -> get())) {
        // Create a websocket session, transferring ownership
        // of both the socket and the HTTP request.
        std::make_shared<WebSocketSession>
        (_socketStream.release_socket()) -> doAccept(_parser -> release());
        return;
    }
    
    //Send the response
    handleRequest(std::move(_parser->release()), _queue);
    
    // If we aren't at the queue limit, try to pipeline another request
    if(! _queue.isFull()) {
        doRead();
    }
}

void HttpSession::OnWrite(bool close, boost::beast::error_code error_code, [[maybe_unused]] size_t bytes_transfered) {
    if (error_code) {
        return fail(error_code, "write");
    }
    if (close) {
        // This means we should close the connection, usually because
        // the response indicated the "Connection: close" semantic.
        doClose();
    }
    // Inform the queue that a write completed
    if(_queue.onWrite()) {
        doRead(); // Read another request
    }
}

void HttpSession::doClose() {
    //Send a TCP shutdown
    boost::beast::error_code error_code;
    _socketStream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_send, error_code);
    if (error_code) {
        fail(error_code, "close");
    }
    // At this point the connection is closed gracefully
}


//Queue class


HttpSession::Queue::Queue(HttpSession& selfSession): _selfSession(selfSession) {
    static_assert(LIMIT > 0, "limit must be positive");
}

bool HttpSession::Queue::isFull() const {
    return _items.size() >= LIMIT;
}

bool HttpSession::Queue::onWrite() {
    BOOST_ASSERT(!_items.empty());
    const bool wasFull = isFull();
    _items.pop_front();
    if (!_items.empty()) {
        (*_items.front())();
    }
    return wasFull;
}
