#pragma once

#include <memory>
#include <boost/asio.hpp>

#include "sudokuBoard.hpp"
#include "sudokuBoardFile.hpp"
#include "ipc_common.hpp"

namespace ba = boost::asio;
using boost::asio::ip::tcp;
using boost::system::error_code;
using TCPSocket = tcp::socket;

class ServerConnection
    : public std::enable_shared_from_this<ServerConnection>
{
    public:
        ServerConnection(TCPSocket socket);

        void start();

    private:
        void doRead();

        void generateSudoku();
        void saveSudoku();

        TCPSocket socket_;

        propertiesPacket properties_;
        sudokuBoard board_;
        sbFile filePacket_;
};

class Server
{
    public:
        using IOContext = ba::io_context;
        using TCPAcceptor = tcp::acceptor;

        Server(IOContext& io, uint16_t port);

    private:
        void doAccept();

        TCPSocket socket_;
        TCPAcceptor acceptor_;
};
