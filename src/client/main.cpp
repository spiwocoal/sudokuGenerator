#include <exception>
#include <iostream>
#include <boost/asio.hpp>

#include "sudokuBoardFile.hpp"
#include "sudokuBoard.hpp"
#include "ipc_common.hpp"
#include "sudokuExporter.hpp"

namespace ba = boost::asio;
using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
    ba::io_context io;

    std::vector<std::string> args(argv, argv + argc);

    switch (args.size()) {
        case 1:
            args = {args.at(0), "localhost", "6869", "45", "9"};
            break;
        case 2:
            args = {args.at(0), args.at(1), "6869", "45", "9"};
            break;
        case 3:
            args = {args.at(0), args.at(1), args.at(2), "45", "9"};
            break;
        case 4:
            args = {args.at(0), args.at(1), args.at(2), args.at(3), "9"};
            break;
        case 5:
            args = {args.at(0), args.at(1), args.at(2), args.at(3), args.at(4)};
            break;
        default:
            std::clog << "usage: " << args.at(0) << " [host = localhost] [port = 6869] [difficulty = 45] [size = 9]" << std::endl;
    }

    try {
        propertiesPacket properties;
        properties.difficulty = std::stoul(args.at(3));
        properties.size = std::stoul(args.at(4));

        tcp::socket socket(io);
        tcp::resolver resolver(io);

        connect(socket, resolver.resolve(args.at(1), args.at(2)));
        write(socket, ba::buffer(&properties, sizeof(properties)));

        sbFile response {};
        size_t length {};
        ba::read(socket, ba::buffer(&length, sizeof(size_t)));
        std::clog << "length: " << length << std::endl;

        response.size = properties.size;
        response.values.resize(length);
        ba::read(socket, ba::buffer(response.values));
        std::clog << "values.size(): " << response.values.size() << std::endl;

        std::string path = "build/receivedBoards/" + Exporter::getTime() + ".sb";
        if (Exporter::writeToFile(response, path)) {
            std::clog << "written to: " << path << std::endl;
        }
        else {
            std::clog << "could not write to: " << path << std::endl;
        }

        sudokuBoard board(response);
        std::clog << board.serialize();

        return 0;
    } catch (std::exception &e) {
        std::clog << e.what() << std::endl;
            return 1;
    }
}
