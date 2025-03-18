#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include "room.hpp"
#include "session.hpp"

using boost::asio::ip::tcp;

void accept_connection(boost::asio::io_context &io, tcp::acceptor &acceptor, Room &room);
void run_server(const std::string &port);

#endif