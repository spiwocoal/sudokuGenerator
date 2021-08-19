#include "sudokuBoardFile.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>

twoCellVal::operator uint8_t() const
{
    return ((val1 << 4) + val0);
}

std::ostream& operator<<(std::ostream& stream, const sbFile& file)
{
    stream.write((char *)&file.size, sizeof(uint8_t));

    for (size_t i {}; i < std::ceil((float)(file.size * file.size) / 2.0f); ++i) {
        stream.write((char*)&file.values[i], sizeof(uint8_t));
    }

    return stream;
}

std::ofstream& operator<<(std::ofstream& stream, const sbFile& file)
{
    stream.write((char *)&file.size, sizeof(uint8_t));

    for (size_t i {}; i < std::ceil((float)(file.size* file.size) / 2.0f); ++i) {
        stream.write((char*)&file.values[i], sizeof(uint8_t));
    }

    return stream;
}

std::ifstream& operator>>(std::ifstream& stream, const sbFile& file)
{

    stream.read((char *)&file.size, sizeof(uint8_t));

    for (size_t i {}; i < std::ceil((float)(file.size* file.size) / 2.0f); ++i) {
        stream.read((char *)&file.values[i], sizeof(uint8_t));
    }

    return stream;
}
