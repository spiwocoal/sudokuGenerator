#include <iostream>
#include <array>
#include <random>
#include <cmath>

namespace Generator {
    void generateSudoku(std::array<std::array<int, 9>, 9> &sudoku, int k);

    void fillDiagonalBoxes(std::array<std::array<int, 9>, 9> &sudoku);

    bool unUsedInBox(int n, int row, int col, std::array<std::array<int, 9>, 9> &sudoku);
    bool unUsedInRow(int n, int row, std::array<std::array<int, 9>, 9> &sudoku);
    bool unUsedInCol(int n, int col, std::array<std::array<int, 9>, 9> &sudoku);

    void removeKDigits(std::array<std::array<int, 9>, 9> &sudoku, int k);

    bool checkIfSafe(int n, int row, int col, std::array<std::array<int, 9>, 9> &sudoku);
    bool findEmptyCell(int &row, int &col, std::array<std::array<int, 9>, 9> &sudoku);

    bool solveSudoku(std::array<std::array<int, 9>, 9> &sudoku);

    void printSudoku(const std::array<std::array<int, 9>, 9> &sudoku);
}
