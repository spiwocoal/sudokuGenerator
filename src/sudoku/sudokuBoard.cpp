#include "sudokuBoard.hpp"
#include <iostream>

sudokuBoard::sudokuBoard()
    : board_(0),
      size_(0)
{
    std::clog << __PRETTY_FUNCTION__ << std::endl;
}

sudokuBoard::sudokuBoard(uint8_t s)
    : board_(s, std::vector<uint8_t>(s)),
      size_(s)
{
    std::clog << __PRETTY_FUNCTION__ << std::endl;
}

sudokuBoard::sudokuBoard(const sbFile &file)
    : board_(file.size, std::vector<uint8_t>(file.size)),
      size_(file.size)
{
    std::clog << __PRETTY_FUNCTION__ << std::endl;
    size_ = file.size;

    uint8_t bytesUsed = ((size_ * size_) % 2 == 0) ? ((size_ * size_) / 2) : ((size_ * size_) / 2 + 1);
    std::vector<uint8_t> flattenedBoard(size_ * size_);

    for (size_t i {}; i < bytesUsed; ++i) {
        flattenedBoard.at(2 * i) = file.values[i].val0;

        if ((2 * i) + 1 < flattenedBoard.size())
            flattenedBoard.at((2 * i) + 1) = file.values[i].val1;
    }

    board_ = unflattenBoard(flattenedBoard);
}

sudokuBoard::~sudokuBoard()
{
    std::clog << __PRETTY_FUNCTION__ << std::endl;

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

std::string sudokuBoard::serialize() const
{
    std::stringstream serializedStream {};

    for (size_t i {}; i < size_; ++i) {
        for (size_t j {}; j < size_; ++j) {
            serializedStream << (int)at(i, j) << (((j + 1) % 3 == 0) ? "  " : "");
        }

        serializedStream << ( ( (i + 1) % 3 == 0 )
                              ? "\n\n" : "\n" );
    }

    return serializedStream.str();
}

sbFile sudokuBoard::to_sbFile() const
{
    uint8_t entriesNeeded = std::ceil((float)(size_ * size_) / 2.0f);

    sbFile file {};
    file.size = size_;
    file.values = std::vector<twoCellVal>(entriesNeeded);

    std::vector<uint8_t> flattenedBoard = flattenBoard();

    for (size_t i {}; i < entriesNeeded; ++i) {
        file.values.at(i).val0 = flattenedBoard.at(2 * i);

        if ((2 * i) + 1 < flattenedBoard.size())
            file.values.at(i).val1 = flattenedBoard.at((2 * i) + 1);
        else
            file.values.at(i).val1 = 0;
    }

    return file;
}

sudokuBoard& sudokuBoard::operator=(const sbFile &rhs)
{
    size_ = rhs.size;
    board_.clear();

    uint8_t bytesUsed = (size_ % 2 == 0) ? (size_ / 2) : (size_ / 2 + 1);
    std::vector<uint8_t> flattenedBoard {};

    for (size_t i {}; i < bytesUsed; ++i) {
        flattenedBoard.at(2 * i) = rhs.values.at(i).val0;

        if ((2 * i) + 1 < flattenedBoard.size())
            flattenedBoard.at((2 * i) + 1) = rhs.values[i].val1;
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
