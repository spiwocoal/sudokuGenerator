#include "sudokuBoard.hpp"

sudokuBoard::sudokuBoard(uint8_t s)
    : board_(s, std::vector<uint8_t>(s))
{
}

sudokuBoard::~sudokuBoard()
{
    for (auto &i : board_) {
        i.clear();
    }
    board_.clear();
}

uint8_t& sudokuBoard::at(size_t r, size_t c)
{
    return board_.at(r).at(c);
}

const uint8_t& sudokuBoard::at(size_t r, size_t c) const
{
    return board_.at(r).at(c);
}

sbFile* sudokuBoard::to_sbFile() const
{
    uint8_t bytesNeeded = (size_ % 2 == 0) ? (size_ / 2) : (size_ / 2 + 1);

    sbFile* file = reinterpret_cast<sbFile *>(malloc(sizeof(struct sbFile) + (bytesNeeded - 1) * sizeof(uint8_t)));
    file->size = size_;
    file->values = reinterpret_cast<twoCellVal*>(malloc(sizeof(twoCellVal) * bytesNeeded));

    std::vector<uint8_t> flattenedBoard = flattenBoard();

    for (uint8_t i {}; i < bytesNeeded; ++i) {
        file->values[i].val0 = flattenedBoard.at(2 * i);
        file->values[i].val1 = flattenedBoard.at(((2 * i) + 1 >= flattenedBoard.size()) ? 0 : flattenedBoard.at((2 * i) + 1));
    }

    return file;
}

sudokuBoard& sudokuBoard::operator=(const sbFile &rhs)
{
    size_ = rhs.size;
    board_.clear();

    uint8_t bytesUsed = (size_ % 2 == 0) ? (size_ / 2) : (size_ / 2 + 1);
    std::vector<uint8_t> flattenedBoard {};

    for (uint8_t i {}; i < bytesUsed; ++i) {
        flattenedBoard.at(2 * i) = rhs.values[i].val0;
        flattenedBoard.at(((2 * i) + 1 >= flattenedBoard.size()) ? 0 : flattenedBoard.at((2 * i) + 1)) = rhs.values[i].val1;
    }

    board_ = unflattenBoard(flattenedBoard);

    return *this;
}

std::vector<uint8_t> sudokuBoard::flattenBoard() const
{
    std::vector<uint8_t> flattenedArray{};

    for (size_t i {}; i < size_; ++i) {
        for (size_t j {}; j < size_; ++j) {
            flattenedArray.push_back(board_.at(i).at(j));
        }
    }

    return flattenedArray;
}

std::vector<std::vector<uint8_t>> sudokuBoard::unflattenBoard(std::vector<uint8_t> flattenedBoard)
{
    std::vector<std::vector<uint8_t>> unflattenedBoard {};

    for (size_t i {}; i < size_; ++i) {
        unflattenedBoard.push_back(std::vector<uint8_t>());

        for (size_t j {}; j < size_; ++j) {
            unflattenedBoard.at(i).push_back(flattenedBoard.at((size_ * i) + j));
        }
    }

    return unflattenedBoard;
}
