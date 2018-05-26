#include "boundedboard.h"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <random>

BoundedBoard::BoundedBoard(int width, int height, std::set<int> stay, std::set<int> born):
    IBoard(stay, born),
    width(width),
    height(height)
{
    field1 = Field(width * height, 0);
    field2 = Field(width * height, 0);
    current = &field1;
}

BoundedBoard::~BoundedBoard() {

}

void BoundedBoard::checkBounds(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        std::stringstream ss;
        ss << "Out of bounds: " << "[" << x << ";" << y << "]";
        throw std::runtime_error(ss.str());
    }
}

int BoundedBoard::getValue(int x, int y) const {
    checkBounds(x, y);
    return getUnsafe(current, x, y);
}

int BoundedBoard::getUnsafe(Field *field, int x, int y) const {
    return field->at(width * y + x);
}

void BoundedBoard::setValue(int x, int y, int value) {
    checkBounds(x, y);
    setUnsafe(current, x, y, value);
}

void BoundedBoard::setUnsafe(Field *field, int x, int y, int value) {
    field->at(width * y + x) = value;
}

void BoundedBoard::random() {
    int x = (std::rand() % (width - 2)) + 1;
    int y = (std::rand() % (height - 2)) + 1;
    int value = getUnsafe(current, x, y);
    setUnsafe(current, x, y, !value);
}

int BoundedBoard::getWidth() const {
    return width;
}

int BoundedBoard::getHeight() const {
    return height;
}

void BoundedBoard::step() {
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

