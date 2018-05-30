#include "iboard.h"

class InfiniteBoard: public IBoard
{
public:
    InfiniteBoard(std::set<int> stay, std::set<int> born): IBoard(stay, born) {}

    void step();

    int getValue(int x, int y) const;
    void setValue(int x, int y, int value);
    Cells getCellsInArea(int x, int y, int width, int height) const;

protected:
    int applyRule(int value, const Cells &neigbours) const;
    Cells getNeighbours(const Cell &cell) const;
    Cells getAliveNeighbours(const Cell &cell) const;
    Cells getDeadCells() const;
    Cells shouldSurvive() const;
    Cells shouldBorn() const;

    Cells cells;
};
