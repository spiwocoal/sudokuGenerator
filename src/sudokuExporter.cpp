#include "sudokuExporter.h"

#include <iostream>

std::string Exporter::getTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm timeNow = *std::localtime(&t);

    std::stringstream buffer;

    buffer << std::put_time(&timeNow, "%F_%T");

    return buffer.str();
}

bool Exporter::writeToFile(const std::array<std::array<int, 9>, 9> &sudokuBoard) {
    bool success = true;

    std::string fileName {getTime() + ".sb"};
    std::ofstream exportFile("sudokuBoards/" + fileName, std::ios::out | std::ios::binary);
    if (!exportFile || exportFile.bad()) {
        success = false;
    }



    return success;
}
