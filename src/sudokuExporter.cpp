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

bool Exporter::writeToFile(const sudokuBoard &sudokuBoard, std::string fpath) {
    bool success = true;

    std::ofstream exportFile(fpath, std::ios::out | std::ios::binary);
    if (!exportFile || exportFile.bad()) {
        success = false;
    }

    sbFile *file = sudokuBoard.to_sbFile();
    exportFile << *file;

    free(file->values);
    free(file);
    return success;
}

bool Exporter::writeToFile(const sudokuBoard &sudokuBoard)
{
    return(writeToFile(sudokuBoard, "sudokuBoards/" + getTime() + ".sb"));
}
