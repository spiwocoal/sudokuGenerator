#pragma once

#include <iostream>
#include <random>
#include <cmath>

#include "sudokuBoard.hpp"

namespace Generator {
    void generateSudoku(sudokuBoard &sudoku, int k);

    void fillDiagonalBoxes(sudokuBoard &sudoku);

    const bool unUsedInBox(int n, int row, int col, sudokuBoard &sudoku);
    const bool unUsedInRow(int n, int row, sudokuBoard &sudoku);
    const bool unUsedInCol(int n, int col, sudokuBoard &sudoku);
    const bool checkIfSafe(int n, int row, int col, sudokuBoard &sudoku);

    const bool findEmptyCell(int &row, int &col, sudokuBoard &sudoku);

    void removeKDigits(sudokuBoard &sudoku, int k);

    bool solveSudoku(sudokuBoard &sudoku);
}
