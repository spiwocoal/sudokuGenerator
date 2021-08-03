#pragma once

#include <fstream>
#include <ctime>
#include <string>
#include <chrono>
#include <iomanip>

#include "sudokuBoard.hpp"

namespace Exporter
{
    std::string getTime();

    bool writeToFile(const sudokuBoard &sudokuBoard, std::string fpath);
    bool writeToFile(const sudokuBoard &sudokuBoard);
}
