#pragma once

#include <memory>
#include <boost/asio.hpp>

#include "sudokuBoard.hpp"
#include "sudokuBoardFile.hpp"
#include "ipc_common.hpp"

class ServerConnection
    : public std::enable_shared_from_this<ServerConnection>
{
    public:
        using TCPSocket = boost::asio::ip::tcp::socket;

        ServerConnection(TCPSocket socket);

        void start();

    private:
        void doRead();
        void doWrite(void* data, size_t length);

        void generateSudoku();

        TCPSocket socket_;

        propertiesPacket* properties_;
        sudokuBoard* board_;
        sbFile* filePacket_;
        short filePacketSize_;
};

class Server
{
    public:
        using IOContext = boost::asio::io_context;
        using TCPSocket = boost::asio::ip::tcp::socket;
        using TCPAcceptor = boost::asio::ip::tcp::acceptor;

        Server(IOContext& io, short port);
        // virtual ~Server();

    private:
        void doAccept();

        TCPSocket socket_;
        TCPAcceptor acceptor_;
};
