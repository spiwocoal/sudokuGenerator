#include "sudokuGenerator.hpp"
#include "sudokuBoard.hpp"

#include <set>

void Generator::generateSudoku(sudokuBoard &sudoku, int k)
{
    // First, we fill the boxes in a diagonal with random valid numbers.
    fillDiagonalBoxes(sudoku);
    solveSudoku(sudoku);
    removeKDigits(sudoku, k);
}


void Generator::fillDiagonalBoxes(sudokuBoard &sudoku)
{
    // Random generator that will give an integer in the range [1,9].
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1,9);

    // Diagonal box index
    for (size_t i {}; i < 3; ++i)
    {
        // We will store the numbers that are already present in the current box
        // in a set so we don't repeat them.
        std::set<int> numbersInBox;

        // Row sub-index in the box
        for (size_t j {}; j < 3; ++j)
        {
            // Column sub-index in the box
            for (size_t k {}; k < 3; ++k)
            {
                int temp = dis(gen);

                while (numbersInBox.find(temp) != numbersInBox.end())
                {
                  temp = dis(gen);
                }

                sudoku.at(j + (3 * i), k + (3 * i)) = temp;
                numbersInBox.insert(temp);
            }
        }
    }
}


const bool Generator::unUsedInBox(int n, int row, int col, sudokuBoard &sudoku)
{
    int vertBoxIndex = col / 3;
    int horiBoxIndex = row / 3;

    for (size_t i {}; i < 3; ++i)
    {
        for (size_t j {}; j < 3; ++j)
        {
            if (sudoku.at(i + (3 * horiBoxIndex), j + (3 * vertBoxIndex)) == n)
            {
                return false;
            }
        }
    }
    return true;
}

const bool Generator::unUsedInRow(int n, int row, sudokuBoard &sudoku)
{
    for (size_t i {}; i < 9; ++i)
    {
        if (sudoku.at(row, i) == n)
        {
            return false;
        }
    }
    return true;
}

const bool Generator::unUsedInCol(int n, int col, sudokuBoard &sudoku)
{
    for (size_t i {}; i < 9; ++i)
    {
        if (sudoku.at(i, col) == n)
        {
            return false;
        }
    }
    return true;
}

const bool Generator::checkIfSafe(int n, int row, int col, sudokuBoard &sudoku)
{
    return (unUsedInBox(n, row, col, sudoku) &&
            unUsedInCol(n, col, sudoku) &&
            unUsedInRow(n, row, sudoku));
}


const bool Generator::findEmptyCell(int &row, int &col, sudokuBoard &sudoku)
{
    for (row = 0; row < 9; ++row)
    {
        for (col = 0; col < 9; ++col)
        {
            if (sudoku.at(row, col) == 0)
            {
                return true;
            }
        }
    }

    return false;
}


void Generator::removeKDigits(sudokuBoard &sudoku, int k)
{
    if (k > 64)
    {
        k = 64;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,8);

    for (int i {}; i < k; ++i)
    {
        int x {};
        int y {};

        do
        {
            x = dis(gen);
            y = dis(gen);
        } while (sudoku.at(x, y) == 0);

        sudoku.at(x, y) = 0;
    }
}


bool Generator::solveSudoku(sudokuBoard &sudoku)
{
    int row {}, col {};

    if (!findEmptyCell(row, col, sudoku))
    {
        return true;
    }

    for (int i {1}; i <= 9; ++i)
    {
        if (checkIfSafe(i, row, col, sudoku))
        {
            sudoku.at(row, col) = i;

            if (solveSudoku(sudoku))
            {
                return true;
            }

            sudoku.at(row, col) = 0;
        }
    }

    return false;
}

// =============================================================================
// =====================================================================================================
// ===========================================================

/*
void Generator::fillRemaining(std::array<std::array<int, 9>, 9> &sudoku)
{
    for(size_t i {}; i < 9; ++i) {
        for(size_t j {}; j < 9; ++j) {                            //            FUUUUUCK
            if(sudoku.at(i).at(j) == 0) {                         //   AFTER SO MUCH FUCKING DEBUGGING
                int num {};                                       //     AND THIS SHIT DOESN'T WORK
                for(size_t k {1}; k < 10; ++k) {                  //               ...
                    if(Generator::checkIfSafe(k, i, j, sudoku)){  //               ...
                        num = k;                                  //   (i guess i need to learn more
                        break;                                    //     about algorithms then...)
                    }                                             //               FML
                }                                                 //    I will leave this here so my
                sudoku.at(i).at(j) = num;                         //    future self can remember how
            }                                                     //           naive I was
        }
    }
}
*/
