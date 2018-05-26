#include "iboard.h"

class InfiniteBoard: public IBoard
{
public:
    InfiniteBoard(std::set<int> stay, std::set<int> born): IBoard(stay, born) {}

    typedef std::pair<int, int> Cell;
    typedef std::set<Cell> Cells;

    void random();
    void step();

    int getValue(int x, int y) const;
    void setValue(int x, int y, int value);
    int getWidth() const;
    int getHeight() const;

    int applyRule(int value, int neigbourCount) const;
    Cells getNeighbours(const Cell &cell) const;
    Cells getAliveNeighbours(const Cell &cell) const;
    Cells getDeadCells() const;
    Cells shouldSurvive() const;
    Cells shouldBorn() const;

protected:
    std::set<Cell> cells;
};
