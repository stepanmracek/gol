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

bool BoundedBoard::checkBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

int BoundedBoard::getValue(int x, int y) const {
    return checkBounds(x, y) ? getUnsafe(current, x, y) : 0;
}

int BoundedBoard::getUnsafe(Field *field, int x, int y) const {
    return field->at(width * y + x);
}

void BoundedBoard::setValue(int x, int y, int value) {
    if (checkBounds(x, y))
        setUnsafe(current, x, y, value);
}

void BoundedBoard::setUnsafe(Field *field, int x, int y, int value) {
    field->at(width * y + x) = value;
}

BoundedBoard::Cells BoundedBoard::getCellsInArea(int x, int y, int width, int height) const {
    Cells result;
    for (int _y = y; _y < y + height; _y++) {
        for (int _x = x; _x < x + width; _x++) {
            if (getValue(_x, _y)) result.insert(Cell(_x, _y));
        }
    }
    return result;
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

