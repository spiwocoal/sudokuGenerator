#include "sudokuGenerator.hpp"
#include "sudokuBoard.hpp"

#include <array>
#include <iostream>
#include <random>
#include <cmath>


namespace Generator {
    // Random generator that will be used later to
    // generate numbers for the board and get random
    // indices to delete from the board
    std::random_device randomDev;
    std::mt19937 randomGen(randomDev());
}


void Generator::generateSudoku(sudokuBoard &sudoku, int k)
{
    // First, we fill the boxes in a diagonal with random valid numbers.
    fillDiagonalBoxes(sudoku);
    solveSudoku(sudoku);
    removeKDigits(sudoku, k);
}


void Generator::fillDiagonalBoxes(sudokuBoard &sudoku)
{
    std::uniform_int_distribution<> numbersDis(1,9);

    // Diagonal box index
    for (size_t i {}; i < 3; ++i)
    {
        // We will store the numbers that are already present in the current box
        // so that we do not repeat them
        std::array<bool, 9> numbersInBox;
        numbersInBox.fill(false);

        // Row sub-index in the box
        for (size_t j {}; j < 3; ++j)
        {
            // Column sub-index in the box
            for (size_t k {}; k < 3; ++k)
            {
                int temp = numbersDis(randomGen);

                while (numbersInBox.at(temp - 1))
                {
                  temp = numbersDis(randomGen);
                }

                sudoku.at(j + (3 * i), k + (3 * i)) = temp;
                numbersInBox.at(temp - 1) = true;
            }
        }
    }
}


bool Generator::unUsedInBox(int n, int row, int col, const sudokuBoard &sudoku)
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

bool Generator::unUsedInRow(int n, int row, const sudokuBoard &sudoku)
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

bool Generator::unUsedInCol(int n, int col, const sudokuBoard &sudoku)
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

bool Generator::checkIfSafe(int n, int row, int col, const sudokuBoard &sudoku)
{
    return (unUsedInBox(n, row, col, sudoku) &&
            unUsedInCol(n, col, sudoku) &&
            unUsedInRow(n, row, sudoku));
}


bool Generator::findEmptyCell(int &row, int &col, const sudokuBoard &sudoku)
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

    std::uniform_int_distribution<> indexDis(0,8);

    for (int i {}; i < k; ++i)
    {
        int x {};
        int y {};

        do
        {
            x = indexDis(randomGen);
            y = indexDis(randomGen);
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
