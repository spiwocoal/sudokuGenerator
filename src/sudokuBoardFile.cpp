#include "sudokuBoardFile.hpp"

std::ostream& operator<<(std::ostream& stream, sbFile& file)
{
    for (size_t i {}; i < 128; ++i) {
        stream.write(reinterpret_cast<char *>(&file.values[i]), sizeof(std::uint8_t));
    }

    return stream;
}

std::ofstream& operator<<(std::ofstream& stream, sbFile& file)
{
    for (size_t i {}; i < 128; ++i) {
        stream.write(reinterpret_cast<char *>(&file.values[i]), sizeof(std::uint8_t));
    }

    return stream;
}

std::ifstream& operator>>(std::ifstream& stream, sbFile& file)
{
    for (size_t i {}; i < 128; ++i) {
        stream.read(reinterpret_cast<char *>(&file.values[i]), sizeof(std::uint8_t));
    }

    return stream;
}
