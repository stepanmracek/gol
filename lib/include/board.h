#pragma once

#include <vector>

class Board {
public:
    Board(int width, int height, std::vector<int> stay, std::vector<int> born);
    virtual ~Board();

    void random();

    int get(int x, int y);
    void set(int x, int y, int value);

private:
    std::vector<int> field1;
    std::vector<int> field2;
    std::vector<int> *current;

    int width;
    int height;
    std::vector<int> stay;
    std::vector<int> born;
};
