#include "board.h"

#include <stdexcept>

Board::Board(int width, int height, std::vector<int> stay, std::vector<int> born):
    width(width),
    height(height),
    stay(stay),
    born(born)
{
    field1 = std::vector<int>(width * height, 0);
    field2 = std::vector<int>(width * height, 0);
    current = &field1;
}

Board::~Board() {

}

int Board::get(int x, int y) {
    return 0;
}

void Board::set(int x, int y, int value) {

}

void Board::random() {

}
