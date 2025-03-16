#ifndef SESSION_HPP
#define SESSION_HPP

#include "room.hpp"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session : public Participant, public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket s, Room &room);
    void start();
    void deliver(Message &message);
    void write(Message &message);
    void async_read();
    void async_write(std::string messageBody, size_t messageLength);

private:
    tcp::socket clientSocket;
    boost::asio::streambuf buffer;
    Room &room;
    std::deque<Message> messageQueue;
};

#endif
