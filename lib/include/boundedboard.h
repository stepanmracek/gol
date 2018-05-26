#pragma once

#include <vector>
#include <set>
#include <ostream>

#include "iboard.h"

class BoundedBoard: public IBoard {
public:
    BoundedBoard(int width, int height, std::set<int> stay, std::set<int> born);
    virtual ~BoundedBoard();

    void random();
    void step();

    int getValue(int x, int y) const;
    void setValue(int x, int y, int value);
    int getWidth() const;
    int getHeight() const;

private:
    typedef std::vector<int> Field;

    void checkBounds(int x, int y) const;
    int getUnsafe(Field *field, int x, int y) const;
    void setUnsafe(Field *field, int x, int y, int value);

    Field field1;
    Field field2;
    Field *current;

    int width;
    int height;
};
