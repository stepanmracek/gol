#include <iostream>

#include "board.h"

int main() {
    Board b(20, 20, {2,3}, {3});
    /*b.setValue(3, 2, 1);
    b.setValue(4, 3, 1);
    b.setValue(4, 4, 1);
    b.setValue(3, 4, 1);
    b.setValue(2, 4, 1);*/

    for (int i = 0; i < 150; i++) {
        b.random();
    }

    std::cout << b;
    std::cout << "----------" << std::endl;
    for (int i = 0; i < 200000; i++) {
        std::string line;
        std::getline(std::cin, line);
        b.step();
        std::cout << b;
        std::cout << "----------" << std::endl;
    }
    return 0;
}
