#pragma once

#include <cstdint>
#include <ostream>
#include <istream>
#include <fstream>
#include <vector>

struct twoCellVal
{
    uint8_t val0 : 4;
    uint8_t val1 : 4;

    operator uint8_t() const;
};

struct sbFile
{                                    // Offset
    uint8_t size;                    // 0x00
    std::vector<twoCellVal> values;  // 0x10
};

std::ostream& operator<<(std::ostream& stream, const sbFile& file);
// Overload << and >> operators on "sbFile" type
std::ofstream& operator<<(std::ofstream& stream, const sbFile& file);
std::ifstream& operator>>(std::ifstream& stream, const sbFile& file);
