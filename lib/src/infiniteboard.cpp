#include "infiniteboard.h"

#include <algorithm>
#include <vector>

int InfiniteBoard::applyRule(int value, const Cells &neigbours) const {
    size_t count = neigbours.size();
    return value ? stay.find(count) != stay.end() : born.find(count) != born.end();
}

InfiniteBoard::Cells InfiniteBoard::getNeighbours(const Cell &cell) const {
    int x = cell.first;
    int y = cell.second;
    return {{x - 1, y - 1}, {x, y - 1}, {x + 1, y - 1}, {x - 1, y}, {x + 1, y}, {x - 1, y + 1}, {x, y + 1}, {x + 1, y + 1}};
}

InfiniteBoard::Cells InfiniteBoard::getAliveNeighbours(const Cell &cell) const {
    auto neighbours = getNeighbours(cell);
    Cells result;
    std::set_intersection(cells.begin(), cells.end(), neighbours.begin(), neighbours.end(), std::inserter(result, result.end()));
    return result;
}

InfiniteBoard::Cells InfiniteBoard::getDeadCells() const {
    Cells allNeighbours;
    std::for_each(cells.begin(), cells.end(), [this, &allNeighbours](const Cell &c) {
        Cells neighbours = getNeighbours(c);
        allNeighbours.insert(neighbours.begin(), neighbours.end());
    });
    Cells result;
    std::set_difference(allNeighbours.begin(), allNeighbours.end(), cells.begin(), cells.end(), std::inserter(result, result.end()));
    return result;
}

InfiniteBoard::Cells InfiniteBoard::shouldSurvive() const {
    Cells result;
    std::copy_if(cells.begin(), cells.end(), std::inserter(result, result.end()), [this](const Cell &c) { return applyRule(1, getAliveNeighbours(c)); });
    return result;
}

InfiniteBoard::Cells InfiniteBoard::shouldBorn() const {
    Cells result;
    Cells deadCells = getDeadCells();
    std::copy_if(deadCells.begin(), deadCells.end(), std::inserter(result, result.end()), [this](const Cell &c) { return applyRule(0, getAliveNeighbours(c)); });
    return result;
}

void InfiniteBoard::step() {
    Cells b = shouldBorn();
    Cells s = shouldSurvive();
    cells.clear();
    std::set_union(b.begin(), b.end(), s.begin(), s.end(), std::inserter(cells, cells.end()));
}

int InfiniteBoard::getValue(int x, int y) const {
    return cells.find({x,y}) != cells.end() ? 1 : 0;
}

void InfiniteBoard::setValue(int x, int y, int value) {
    if (value) {
        cells.insert({x, y});
    } else {
        cells.erase({x, y});
    }
}

InfiniteBoard::Cells InfiniteBoard::getCellsInArea(int x, int y, int width, int height) const {
    Cells result;
    std::copy_if(cells.begin(), cells.end(), std::inserter(result, result.end()), [&](const Cell &c) {
        return c.first >= x && c.second >= y && c.first <= x + width && c.second <= y + height;
    });
    return result;
}
