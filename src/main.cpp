#include "sudokuGenerator.hpp"
#include "sudokuExporter.hpp"

#include <array>
#include <string.h>

enum difficulty
{
    EASY = 45,
    MEDIUM = 50,
    HARD = 58,
    EXPERT = 64
};

bool isNumber(const std::string& str);

int main(int argc, char* argv[])
{
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
            std::cout << "The non-numeric argument given does not match one of the defined difficulty levels." << std::endl;
            return 1;
        }
    }

    std::array<std::array<int, 9>, 9> sudoku {};
    Generator::generateSudoku(sudoku, holes);
    Generator::printSudoku(sudoku);

    //Exporter::createFile();

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
