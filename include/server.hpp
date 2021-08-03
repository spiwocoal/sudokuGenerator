#pragma once

#include <memory>

#include <boost/asio/io_context.hpp>

class ServerConnection
    : public std::enable_shared_from_this<ServerConnection>
{
    public:
        ServerConnection(boost::asio::::ip::tcp::socket socket);

};

class Server
{
    public:
        Server(boost::asio::io_context& io, short port);
        // virtual ~Server();

};
