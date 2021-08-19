#include <iostream>
#include <boost/asio/io_context.hpp>

#include "server.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    try {
        boost::asio::io_context io;
        Server server(io, std::stoi(argv[1]));

        io.run();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
