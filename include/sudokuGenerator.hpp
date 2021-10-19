#pragma once

#include "sudokuBoard.hpp"

namespace Generator {
    void generateSudoku(sudokuBoard &sudoku, int k);

    void fillDiagonalBoxes(sudokuBoard &sudoku);

    bool unUsedInBox(int n, int row, int col, const sudokuBoard &sudoku);
    bool unUsedInRow(int n, int row, const sudokuBoard &sudoku);
    bool unUsedInCol(int n, int col, const sudokuBoard &sudoku);
    bool checkIfSafe(int n, int row, int col, const sudokuBoard &sudoku);

    bool findEmptyCell(int &row, int &col, const sudokuBoard &sudoku);

    void removeKDigits(sudokuBoard &sudoku, int k);

    bool solveSudoku(sudokuBoard &sudoku);
}
