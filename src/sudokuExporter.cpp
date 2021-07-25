#include "sudokuExporter.hpp"
#include "sudokuBoardFile.hpp"

#include <cmath>

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
    if (!exportFile || exportFile.bad())
    {
        success = false;
    }

    struct sbFile *file = reinterpret_cast<sbFile *>(malloc(sizeof(struct sbFile) + std::ceil((float)(9 * 9) / 2.0f) * sizeof(uint8_t)));
    file->size = {9, 9};

    size_t fileIndex {};

    std::array<int, 81> flattenedArray {};
    for (size_t i {}; i < 9; ++i) {
        for (size_t j {}; j < 9; ++j) {
            flattenedArray.at((9 * i) + j) = sudokuBoard.at(i).at(j);
        }
    }

    while (fileIndex < std::ceil((float)(9 * 9) / 2.0f)) {
        file->values[fileIndex].val0 = flattenedArray.at(2 * fileIndex);
        file->values[fileIndex].val1 = ((2 * fileIndex) + 1) >= flattenedArray.size() ? 0 : flattenedArray.at((2 * fileIndex) + 1);

        ++fileIndex;
    }

    exportFile << *file;

    free(file);
    return success;
}
