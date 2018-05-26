#include "infiniteboard.h"

#include <algorithm>

int InfiniteBoard::applyRule(int value, int neigbourCount) const {
    return value ? stay.find(neigbourCount) != stay.end() : born.find(neigbourCount) != born.end();
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
    for (const Cell &c : cells) {
        for (const Cell &n : getNeighbours(c)) {
            allNeighbours.insert(n);
        }
    }
    Cells result;
    std::set_difference(allNeighbours.begin(), allNeighbours.end(), cells.begin(), cells.end(), std::inserter(result, result.end()));
    return result;
}

InfiniteBoard::Cells InfiniteBoard::shouldSurvive() const {
    Cells result;
    for (const Cell &cell: cells) {
        if (applyRule(1, getAliveNeighbours(cell).size()))
            result.insert(cell);
    }
    return result;
}

InfiniteBoard::Cells InfiniteBoard::shouldBorn() const {
    Cells result;
    Cells deadCells = getDeadCells();
    for (const Cell &c : deadCells) {
        if (applyRule(0, getAliveNeighbours(c).size()))
            result.insert(c);
    }
    return result;
}

void InfiniteBoard::random() {

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

int InfiniteBoard::getWidth() const {
    return 500;
}

int InfiniteBoard::getHeight() const {
    return 500;
}
