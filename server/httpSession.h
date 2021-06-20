#ifndef HTTP_SESSION_H
#define HTTP_SESSION_H


#include <utility>
#include <memory>
#include <optional>
#include <deque>

#include <boost/asio.hpp>
#include <boost/beast.hpp>


#include "serverUtility.h"
#include "webSocketSession.h"
#include "requestProcessor.h"

class HttpSession: public std::enable_shared_from_this<HttpSession> {
public:
    //Take ownership of the socket
    HttpSession(boost::asio::ip::tcp::socket&& socket);
    void Run();
    
private:
    
    void doRead();
    void onRead(boost::beast::error_code error_code, [[maybe_unused]] size_t bytes_transfered);
    void OnWrite(bool close, boost::beast::error_code error_code, [[maybe_unused]] size_t bytes_transfered) ;
    void doClose();
    
    
    
    
    class Queue {
    public:
        explicit Queue(HttpSession& selfSession);
        
        //Returns true if we reached the end of the queue
        bool isFull() const;
        
        //Called when a message finished read
        //Returns true if the caller should initiate a read
        bool onWrite();
        
        //Called by Http handler to send the response
        template<bool isRequest, typename Body, typename Fields>
        void operator()(boost::beast::http::message<isRequest, Body, Fields>&& message);
        
    private:
        static constexpr size_t LIMIT = 8; //Max namber of session that will queued
        struct Work { //Interface that stored
            virtual ~Work() = default;
            virtual void operator()() = 0;
        };
        HttpSession& _selfSession;
        std::deque<std::unique_ptr<Work>> _items;
    };
    
    
    
    
    boost::beast::tcp_stream _socketStream;
    boost::beast::flat_buffer _dynamicBuffer;
    
    Queue _queue;
    
    std::optional<boost::beast::http::request_parser<boost::beast::http::string_body>> _parser;
    
};


template<bool isRequest, typename Body, typename Fields>
void HttpSession::Queue::operator()(boost::beast::http::message<isRequest, Body, Fields>&& message) {
    //This holds a work item
    struct WorkImpl : Work {
        HttpSession& _selfSession;
        boost::beast::http::message<isRequest, Body, Fields> _message;
        
        WorkImpl(HttpSession& selfSession, boost::beast::http::message<isRequest, Body, Fields>&& message)
            : _selfSession(selfSession), _message(std::move(message)) {}
        
        void operator() () {
            boost::beast::http::async_write(_selfSession._socketStream, _message,
                    boost::beast::bind_front_handler(&HttpSession::OnWrite, _selfSession.shared_from_this(), _message.need_eof()));
        }
    };
    
    _items.push_back(std::make_unique<WorkImpl>(_selfSession, std::move(message)));
    
    // If there was no previous work, start this one
    if(_items.size() == 1)
        (*_items.front())();
}



#endif
