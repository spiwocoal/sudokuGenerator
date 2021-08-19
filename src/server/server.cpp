#include "server.hpp"
#include "sudokuExporter.hpp"
#include "sudokuGenerator.hpp"

ServerConnection::ServerConnection(TCPSocket socket)
    : socket_(std::move(socket))
{ }

void ServerConnection::start()
{
    std::clog << __PRETTY_FUNCTION__ << std::endl;
    doRead();
}

void ServerConnection::doRead()
{
    std::clog << __PRETTY_FUNCTION__ << std::endl;
    auto self(shared_from_this());
    socket_.async_read_some(ba::buffer(&properties_, sizeof(properties_)),
                            [this, self](error_code ec, std::size_t length)
                            {
                                std::clog << "received " << length << std::endl;
                                if (!ec) {
                                    generateSudoku();

                                    size_t length[] { filePacket_.values.size() };

                                    std::vector<ba::const_buffer> msg {
                                        ba::buffer(length),
                                        ba::buffer(filePacket_.values)};
                                    std::clog << "length: " << length[0] << std::endl;

                                    ba::async_write(socket_, msg,
                                                    [this, self = shared_from_this()](error_code ec, std::size_t length)
                                                    {
                                                        std::clog << "written " << length << std::endl;
                                                        if (!ec) doRead();
                                                    });
                                }
                            });
}

void ServerConnection::generateSudoku()
{
    std::clog << __PRETTY_FUNCTION__ << std::endl;
    uint8_t size = properties_.size;
    uint8_t difficulty = properties_.difficulty;

    board_ = sudokuBoard(size);
    Generator::generateSudoku(board_, difficulty);
    saveSudoku();
    std::clog << board_.serialize();

    filePacket_ = board_.to_sbFile();
}

void ServerConnection::saveSudoku()
{
    std::clog << __PRETTY_FUNCTION__ << std::endl;
    std::string path = "build/generatedBoards/" + Exporter::getTime() + ".sb";

    if (Exporter::writeToFile(board_, path)) {
        std::clog << "written to: " << path << std::endl;
    }
    else {
        std::clog << "could not write to: " << path << std::endl;
    }
}



Server::Server(IOContext& io, uint16_t port)
    : socket_(io),
      acceptor_(io, {tcp::v4(), port})
{
    doAccept();
}

void Server::doAccept()
{
    std::clog << __PRETTY_FUNCTION__ << std::endl;
    acceptor_.async_accept(socket_,
        [this](error_code ec)
        {
            if (!ec) {
                std::clog << "Accepted " << socket_.remote_endpoint() << std::endl;
                std::make_shared<ServerConnection>(std::move(socket_))->start();
                doAccept();
            }
            else {
                std::clog << "Accept " << ec.message() << std::endl;
            }
        });
}
