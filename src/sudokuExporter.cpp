#include "sudokuExporter.hpp"
#include "sudokuBoardFile.hpp"

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

    sbFile file;
    file.size = {9, 9};

    // FIXME: Indexing for file.values is wrong
    // TODO: j should be stepped by one, while still storing 2 cells per byte
    for (size_t i {}; i < 9; ++i) {
        for (size_t j {}; j < 8; j += 2) {
            file.values[(9 * i) + j].val0 = sudokuBoard.at(i).at(j);
            file.values[(9 * i) + j].val1 = sudokuBoard.at(i).at(j + 1);
        }
    }

    exportFile << file;

    return success;
}
