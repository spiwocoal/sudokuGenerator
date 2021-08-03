#include <iostream>
#include <boost/asio.hpp>

#include "sudokuBoardFile.hpp"
#include "sudokuBoard.hpp"

struct propertiesPacket
{
    uint8_t difficulty;
    uint8_t size;
};

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <host> <port> [difficulty = 45] [size = 9]" << std::endl;
        return 1;
    }

    propertiesPacket properties;
    properties.difficulty = (argc < 4) ? 45 : std::stoi(argv[3]);
    properties.size = (argc < 5) ? 9 : std::stoi(argv[4]);

    boost::asio::io_context io;
    boost::asio::ip::tcp::socket socket(io);
    boost::asio::ip::tcp::resolver resolver(io);

    boost::asio::connect(socket, resolver.resolve(argv[1], argv[2]));
    boost::asio::write(socket, boost::asio::buffer(&properties, sizeof(propertiesPacket)));

    unsigned short responseSize {};
    boost::asio::read(socket, boost::asio::buffer(&responseSize, sizeof(short)));

    sbFile* response = reinterpret_cast<sbFile*>(malloc(responseSize));
    boost::asio::read(socket, boost::asio::buffer(response, responseSize));

    sudokuBoard board(*response);

    return 0;
}
