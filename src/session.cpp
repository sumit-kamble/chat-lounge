#include "session.hpp"

Session::Session(tcp::socket s, Room &r) : clientSocket(std::move(s)), room(r) {};

void Session::start()
{
    room.join(shared_from_this());
    async_read();
}

void Session::deliver(Message &message)
{
    room.deliver(shared_from_this(), message);
}

void Session::write(Message &message)
{
    messageQueue.push_back(message);
    while (messageQueue.size() != 0)
    {
        Message message = messageQueue.front();
        messageQueue.pop_front();
        bool header_decode = message.decodeHeader();
        if (header_decode)
        {
            std::string body = message.getBody();
            async_write(body, message.getBodyLength());
        }
        else
        {
            std::cout << "Mesage length exceeds the max length" << std::endl;
        }
    }
}

void Session::async_read()
{
    auto self(shared_from_this());
    boost::asio::async_read_until(clientSocket, buffer, "\n", [this, self](boost::system::error_code ec, std::size_t bytes_transferred)
                                  {
        if(!ec){
            std::string data(boost::asio::buffers_begin(buffer.data()),
            boost::asio::buffers_begin(buffer.data()) + bytes_transferred);

            buffer.consume(bytes_transferred);
            std::cout<<"Received: " << data << std::endl;
            Message message(data);
            deliver(message);
            async_read();
        }else{
            room.leave(shared_from_this());
            if(ec == boost::asio::error::eof){
                std::cout << "Connection closed by peer" << std::endl;
            }else{
                std::cout << "Read error: " << ec.message() << std::endl;
            }
        } });
}

void Session::async_write(std::string messageBody, size_t messageLength)
{
    auto write_handler = [&](boost::system::error_code ec, std::size_t bytes_transferred)
    {
        if (!ec)
        {
            std::cout << "Data is written to the socket: " << std::endl;
        }
        else
        {
            std::cerr << "Write error: " << ec.message() << std::endl;
        }
    };
    boost::asio::async_write(clientSocket, boost::asio::buffer(messageBody, messageLength), write_handler);
}
