#pragma once

#include <cstdint>
#include <ostream>
#include <istream>
#include <fstream>

struct boardSize
{
    uint8_t rows : 4;
    uint8_t cols : 4;
};

struct twoCellVal
{
    uint8_t val0 : 4;
    uint8_t val1 : 4;
};

struct sbFile
{                                    // Offset
    boardSize size;                  // 0x00
    twoCellVal values [128];         // 0x10
};

std::ostream& operator<<(std::ostream& stream, sbFile& file);
// Overload << and >> operators on "sbFile" type
std::ofstream& operator<<(std::ofstream& stream, sbFile& file);
std::ifstream& operator>>(std::ifstream& stream, sbFile& file);
