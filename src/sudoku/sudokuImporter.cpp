#include "sudokuImporter.hpp"
#include "sudokuBoardFile.hpp"

#include <cmath>
#include <fstream>

sudokuBoard Importer::readFromFile(const std::string& path)
{
    std::array<int, 81> flattenedBoard;
    std::ifstream inputFile(path);

    struct sbFile *file = reinterpret_cast<sbFile *>(malloc(sizeof(struct sbFile) + std::ceil((float)(9 * 9) / 2.0f) * sizeof(uint8_t)));
    inputFile >> *file;

    for (size_t i {}; i < std::ceil((float)(9 * 9) / 2.0f); ++i)
    {
        flattenedBoard.at(2 * i) = file->values[i].val0;
        if ((2 * i) + 1 < 81) flattenedBoard.at((2 * i) + 1) = file->values[i].val1;
    }

    sudokuBoard board(9);

    for (size_t i {}; i < 9; ++i)
    {
        for (size_t j {}; j < 9; ++j)
        {
            board.at(i, j) = flattenedBoard.at((9 * i) + j);
        }
    }

    return board;
}
