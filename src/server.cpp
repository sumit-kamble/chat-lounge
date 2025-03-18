#include "server.hpp"

void accept_connection(boost::asio::io_context &io, tcp::acceptor &acceptor, Room &room)
{
    acceptor.async_accept(
        [&](boost::system::error_code ec, tcp::socket socket)
        {
            if (ec)
            {
                std::cerr << "Failed to accept connection: " << ec.message() << std::endl;
            }
            else
            {
                std::shared_ptr<Session> session = std::make_shared<Session>(std::move(socket), room);
                session->start();
            }
            accept_connection(io, acceptor, room);
        });
}

void run_server(const std::string &port)
{
    boost::asio::io_context io_context;
    Room room;

    tcp::endpoint endpoint(tcp::v4(), std::stoi(port));
    tcp::acceptor acceptor(io_context, endpoint);

    accept_connection(io_context, acceptor, room);
    io_context.run();
}