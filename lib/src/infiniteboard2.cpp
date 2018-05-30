#include "infiniteboard2.h"

#include <algorithm>

int InfiniteBoard2::getValue(int x, int y) const {
    return cells.find({x,y}) != cells.end() ? 1 : 0;
}

void InfiniteBoard2::setValue(int x, int y, int value) {
    if (value) {
        cells.insert({x, y});
    } else {
        cells.erase({x, y});
    }
}

IBoard::Cells InfiniteBoard2::getCellsInArea(int x, int y, int width, int height) const {
    IBoard::Cells result;
    std::copy_if(cells.begin(), cells.end(), std::inserter(result, result.end()), [&](const Cell &c) {
        return c.first >= x && c.second >= y && c.first <= x + width && c.second <= y + height;
    });
    return result;
}

void InfiniteBoard2::step() {
    auto getNeighbours = [&](const Cell &cell) {
        int x = cell.first;
        int y = cell.second;
        return Cells({{x - 1, y - 1}, {x, y - 1}, {x + 1, y - 1}, {x - 1, y}, {x + 1, y}, {x - 1, y + 1}, {x, y + 1}, {x + 1, y + 1}});
    };

    auto getAliveNeighboursCount = [&](const Cell &cell) {
        auto neighbours = getNeighbours(cell);
        int count = 0;
        for (const Cell &nc : neighbours) {
            if (cells.find(nc) != cells.end())
                count++;
        }
        return count;
    };

    auto getDeadNeighbours = [&](const Cell &cell) {
        auto neighbours = getNeighbours(cell);
        Cells result;
        std::copy_if(neighbours.begin(), neighbours.end(), std::inserter(result, result.end()), [&](const Cell &nc) {
            return cells.find(nc) == cells.end();
        });
        return result;
    };

    Cells result;
    Cells deadCells;
    for (const Cell &cell : cells) {
        auto aliveNeighbours = getAliveNeighboursCount(cell);
        if (stay.find(aliveNeighbours) != stay.end())
            result.insert(cell);

        auto deadNeighbours = getDeadNeighbours(cell);
        for (const Cell &dn : deadNeighbours) {
            if (deadCells.find(dn) == deadCells.end()) {
                deadCells.insert(dn);
                auto aliveNeighbours = getAliveNeighboursCount(dn);
                if (born.find(aliveNeighbours) != born.end())
                    result.insert(dn);
            }
        }
    }
    cells = result;
}
