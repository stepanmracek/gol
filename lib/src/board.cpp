#include "board.h"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <random>

Board::Board(int width, int height, std::set<int> stay, std::set<int> born):
    width(width),
    height(height),
    stay(stay),
    born(born)
{
    field1 = Field(width * height, 0);
    field2 = Field(width * height, 0);
    current = &field1;
}

Board::~Board() {

}

void Board::checkBounds(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        std::stringstream ss;
        ss << "Out of bounds: " << "[" << x << ";" << y << "]";
        throw std::runtime_error(ss.str());
    }
}

int Board::getValue(int x, int y) const {
    checkBounds(x, y);
    return getUnsafe(current, x, y);
}

int Board::getUnsafe(Field *field, int x, int y) const {
    return field->at(width * y + x);
}

void Board::setValue(int x, int y, int value) {
    checkBounds(x, y);
    setUnsafe(current, x, y, value);
}

void Board::setUnsafe(Field *field, int x, int y, int value) {
    field->at(width * y + x) = value;
}

void Board::random() {
    int x = (std::rand() % (width - 2)) + 1;
    int y = (std::rand() % (height - 2)) + 1;
    int value = getUnsafe(current, x, y);
    setUnsafe(current, x, y, !value);
}

int Board::getWidth() const {
    return width;
}

int Board::getHeight() const {
    return height;
}

void Board::step() {
    Field *other = (&field1 == current ? &field2 : &field1);
    for (int y = 1; y < height- 1; y++) {
        for (int x = 1; x < height - 1; x++) {
            int count = getUnsafe(current, x - 1, y - 1) + getUnsafe(current, x, y - 1) + getUnsafe(current, x + 1, y - 1) +
                    getUnsafe(current, x - 1, y) + getUnsafe(current, x + 1, y) +
                    getUnsafe(current, x - 1, y + 1) + getUnsafe(current, x, y + 1) + getUnsafe(current, x + 1, y + 1);

            int alive = getUnsafe(current, x, y);
            if (alive) {
                if (stay.find(count) != stay.end()) {
                    setUnsafe(other, x, y, 1);
                } else {
                    setUnsafe(other, x, y, 0);
                }
            } else {
                if (born.find(count) != born.end()) {
                    setUnsafe(other, x, y, 1);
                } else {
                    setUnsafe(other, x, y, 0);
                }
            }
        }
    }
    current = other;
}

std::ostream &operator<<(std::ostream &stream, const Board &board) {
    for (int y = 0; y < board.getHeight(); y++) {
        for (int x = 0; x < board.getWidth(); x++) {
            stream << (board.getValue(x, y) ? "x" : " ");
        }
        stream << std::endl;
    }
    return stream;
}
