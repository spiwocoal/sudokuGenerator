#pragma once

#include <fstream>
#include <ctime>
#include <string>
#include <chrono>
#include <iomanip>

namespace Exporter
{
    std::string getTime();

    bool writeToFile(const std::array<std::array<int, 9>, 9> &sudokuBoard);
}
