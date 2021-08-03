#include "sudokuGenerator.hpp"
#include "sudokuExporter.hpp"
#include "sudokuImporter.hpp"
#include "sudokuBoard.hpp"

#include <array>
#include <string.h>
#include <string>

bool isNumber(const std::string& str);

enum difficulty
{
    EASY = 45,
    MEDIUM = 50,
    HARD = 58,
    EXPERT = 64
};

int main(int argc, char* argv[])
{
    sudokuBoard sudoku(9);

    if (argc > 2)
    {
        std::cerr << "Only one argument can be used." << std::endl;
        return  1;
    }

    int holes {};

    if (argc == 1)
    {
        holes = MEDIUM;
    }
    else if (isNumber(argv[1]))
    {
        holes = std::atoi(argv[1]);
    }
    else
    {
        if (strcmp(argv[1], "easy") == 0)
        {
            holes = EASY;
        }
        else if (strcmp(argv[1], "medium") == 0)
        {
            holes = MEDIUM;
        }
        else if (strcmp(argv[1], "hard") == 0)
        {
            holes = HARD;
        }
        else if (strcmp(argv[1], "expert") == 0)
        {
            holes = EXPERT;
        }
        else
        {
            sudoku = Importer::readFromFile(std::string(argv[1]));
            Generator::printSudoku(sudoku);

            return 0;
        }
    }

    Generator::generateSudoku(sudoku, holes);
    Generator::printSudoku(sudoku);

    Exporter::writeToFile(sudoku);

    return 0;
}

bool isNumber(const std::string& str)
{
    for (const char& c : str)
    {
        if (std::isdigit(c) == 0) return false;
    }

    return true;
}
