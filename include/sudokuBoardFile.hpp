#pragma once

#include <cstdint>
#include <ostream>
#include <istream>
#include <fstream>

struct twoCellVal
{
    uint8_t val0 : 4;
    uint8_t val1 : 4;
};

struct sbFile
{                                    // Offset
    uint8_t size;                    // 0x00
    twoCellVal* values;              // 0x10
};

std::ostream& operator<<(std::ostream& stream, sbFile& file);
// Overload << and >> operators on "sbFile" type
std::ofstream& operator<<(std::ofstream& stream, sbFile& file);
std::ifstream& operator>>(std::ifstream& stream, sbFile& file);
