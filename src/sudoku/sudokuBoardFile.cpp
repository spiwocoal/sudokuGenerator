#include "sudokuBoardFile.hpp"
#include <cmath>

std::ostream& operator<<(std::ostream& stream, sbFile& file)
{
    stream.write(reinterpret_cast<char *>(&file.size), sizeof(uint8_t));

    for (size_t i {}; i < std::ceil((float)(file.size * file.size) / 2.0f); ++i)
    {
        stream.write(reinterpret_cast<char *>(&file.values[i]), sizeof(uint8_t));
    }

    return stream;
}

std::ofstream& operator<<(std::ofstream& stream, sbFile& file)
{
    stream.write(reinterpret_cast<char *>(&file.size), sizeof(uint8_t));

    for (size_t i {}; i < std::ceil((float)(file.size* file.size) / 2.0f); ++i)
    {
        stream.write(reinterpret_cast<char *>(&file.values[i]), sizeof(uint8_t));
    }

    return stream;
}

std::ifstream& operator>>(std::ifstream& stream, sbFile& file)
{
    stream.read(reinterpret_cast<char *>(&file.size), sizeof(uint8_t));

    for (size_t i {}; i < std::ceil((float)(file.size* file.size) / 2.0f); ++i)
    {
        stream.read(reinterpret_cast<char *>(&file.values[i]), sizeof(uint8_t));
    }

    return stream;
}
