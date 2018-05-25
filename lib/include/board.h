#pragma once

#include <vector>
#include <set>
#include <ostream>

class Board {
public:
    Board(int width, int height, std::set<int> stay, std::set<int> born);
    virtual ~Board();

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
    std::set<int> stay;
    std::set<int> born;
};

std::ostream &operator<<(std::ostream &stream, const Board &board);
