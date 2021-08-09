#include "server.hpp"
#include "sudokuGenerator.hpp"

ServerConnection::ServerConnection(TCPSocket socket)
    : socket_(std::move(socket))
{
}

void ServerConnection::start()
{
    doRead();
}

void ServerConnection::doRead()
{
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(properties_, sizeof(propertiesPacket)),
                            [this, self](boost::system::error_code ec, std::size_t length)
                            {
                                if (!ec) {
                                    generateSudoku();
                                    doWrite(&filePacketSize_, sizeof(short));

                                    doWrite(filePacket_, sizeof(*filePacket_));
                                }
                            });
}

void ServerConnection::doWrite(void* data, size_t length)
{
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data, length),
                             [this, self](boost::system::error_code ec, std::size_t length)
                             {
                                 if (!ec) {
                                     doRead();
                                 }
                             });
}

void ServerConnection::generateSudoku()
{
    uint8_t size = properties_->size;
    uint8_t difficulty = properties_->difficulty;

    board_ = new sudokuBoard(size);
    Generator::generateSudoku(*board_, difficulty);

    filePacket_ = board_->to_sbFile();
    filePacketSize_ = sizeof(*filePacket_);
}


Server::Server(IOContext& io, short port)
    : socket_(io),
      acceptor_(io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    doAccept();
}

void Server::doAccept()
{
    acceptor_.async_accept(
        [this](boost::system::error_code ec)
        {
            if (!ec) {
                std::make_shared<ServerConnection>(std::move(socket_))->start();
            }

            doAccept();
        });
}
