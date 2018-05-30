#pragma once

#include <unordered_set>

#include "iboard.h"

struct PairHasher {
    inline size_t operator()(const std::pair<int, int> &v) const {
        std::hash<int> intHasher;
        return intHasher(v.first) ^ intHasher(v.second);
    }
};

class InfiniteBoard2: public IBoard {
public:
    InfiniteBoard2(std::set<int> stay, std::set<int> born): IBoard(stay, born) {}

    typedef std::unordered_set<Cell, PairHasher> Cells;

    virtual void step();
    virtual int getValue(int x, int y) const;
    virtual void setValue(int x, int y, int value);
    virtual IBoard::Cells getCellsInArea(int x, int y, int width, int height) const;

private:
    Cells cells;
};
