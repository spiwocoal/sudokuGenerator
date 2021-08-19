#pragma once

#include "sudokuBoardFile.hpp"

#include <cstddef>
#include <sstream>
#include <vector>
#include <cstdint>
#include <cmath>

class sudokuBoard {
    std::vector<std::vector<uint8_t>> board_;

    public:
        sudokuBoard();
        sudokuBoard(uint8_t s);
        sudokuBoard(const sbFile &file);
        virtual ~sudokuBoard();

        uint8_t& at(size_t r, size_t c);
        const uint8_t& at(size_t r, size_t c) const;

        std::string serialize() const;

        sbFile to_sbFile() const;

        std::vector<uint8_t> flattenBoard() const;
        std::vector<std::vector<uint8_t>> unflattenBoard(std::vector<uint8_t> flattenedBoard);

        sudokuBoard& operator=(const sbFile &rhs);

    private:
        uint8_t size_;
};
