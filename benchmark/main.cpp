#include <map>
#include <ctime>
#include <iostream>
#include <fstream>

#include "infiniteboard.h"
#include "infiniteboard2.h"
#include "boundedboard.h"

typedef std::pair<std::string, IBoard::Ptr> Pair;
typedef std::map<std::string, IBoard::Ptr> Map;

int main() {
    std::set<int> stay = {2, 3};
    std::set<int> born = {3};

    std::map<std::string, std::ofstream> outputs;
    outputs["bounded"].open("bounded");
    outputs["infinite"].open("infinite");
    outputs["infinite2"].open("infinite2");

    for (int fieldSize = 10; fieldSize <= 250; fieldSize += 10) {
        int cellCount = fieldSize*fieldSize*0.25;
        Map boards;
        boards["bounded"].reset(new BoundedBoard(fieldSize, fieldSize, stay, born));
        boards["infinite"].reset(new InfiniteBoard(stay, born));
        boards["infinite2"].reset(new InfiniteBoard2(stay, born));

        for (int cell = 0; cell < cellCount; cell++) {
            int x = rand() % fieldSize;
            int y = rand() % fieldSize;

            for (const Pair &pair: boards) {
                pair.second->setValue(x, y, 1);
            }
        }

        std::map<std::string, int> elapsedTimes;
        for (int step = 0; step < 100; step++) {
            for (const Pair &pair: boards) {
                clock_t begin = std::clock();
                pair.second->step();
                clock_t end = std::clock();
                double elapsed = 1000.0 * (double(end - begin) / CLOCKS_PER_SEC);
                elapsedTimes[pair.first] += elapsed;
            }
        }
        for (auto &pair : elapsedTimes) {
            pair.second /= 100;
            std::cout << cellCount << " " << pair.first << ": " << pair.second << "ms" << std::endl;

            outputs[pair.first] << cellCount << " " << pair.second << std::endl;
        }
    }

}
