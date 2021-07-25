#pragma once

#include <array>
#include <string>

namespace Importer
{
    std::array<std::array<int, 9>, 9> readFromFile(const std::string& path);
}
