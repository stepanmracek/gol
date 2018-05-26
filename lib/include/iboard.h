#pragma once

#include <set>
#include <ostream>
#include <memory>

class IBoard {
public:
    typedef std::shared_ptr<IBoard> Ptr;

    IBoard(std::set<int> stay, std::set<int> born): stay(stay), born(born) {}
    virtual ~IBoard() {}

    virtual void random() = 0;
    virtual void step() = 0;

    virtual int getValue(int x, int y) const = 0;
    virtual void setValue(int x, int y, int value) = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

protected:
    std::set<int> stay;
    std::set<int> born;
};

/*std::ostream &operator<<(std::ostream &stream, const IBoard &board) {
    for (int y = 0; y < board.getHeight(); y++) {
        for (int x = 0; x < board.getWidth(); x++) {
            stream << (board.getValue(x, y) ? "x" : " ");
        }
        stream << std::endl;
    }
    return stream;
}*/
