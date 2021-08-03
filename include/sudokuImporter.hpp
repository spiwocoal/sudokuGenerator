#pragma once

#include <array>
#include <string>

#include "sudokuBoard.hpp"

namespace Importer
{
    sudokuBoard readFromFile(const std::string& path);
}
