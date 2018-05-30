#include "gtest/gtest.h"
#include "infiniteboard.h"

/*
  0 1 2 3
0 o o o
1 o x o o
2 o x x o
3 o o o o
*/
class InfiniteBoardTestFixture : public InfiniteBoard, public testing::Test
{
public:
    InfiniteBoardTestFixture() : InfiniteBoard({2,3}, {3}) {}

    void SetUp() {
        setValue(1, 1, 1);
        setValue(1, 2, 1);
        setValue(2, 2, 1);
    }
};

TEST_F(InfiniteBoardTestFixture, testSetGet) {
    InfiniteBoard::Cells cells  = getCellsInArea(0, 0, 3, 3);
    EXPECT_EQ(cells.size(), 3);

    EXPECT_TRUE(cells.find({1,1}) != cells.end());
    EXPECT_TRUE(getValue(1,1));

    EXPECT_TRUE(cells.find({1,2}) != cells.end());
    EXPECT_TRUE(getValue(1,2));

    EXPECT_TRUE(cells.find({2,2}) != cells.end());
    EXPECT_TRUE(getValue(2,2));

    EXPECT_TRUE(cells.find({2,1}) == cells.end());
    EXPECT_EQ(getValue(2,1), 0);
}

TEST_F(InfiniteBoardTestFixture, testGetNeighboours) {
    Cells neigbours = getAliveNeighbours({2,1});
    EXPECT_EQ(neigbours.size(), 3);
    EXPECT_TRUE(neigbours.find({1,1}) != neigbours.end());
    EXPECT_TRUE(neigbours.find({1,2}) != neigbours.end());
    EXPECT_TRUE(neigbours.find({1,2}) != neigbours.end());
    EXPECT_TRUE(neigbours.find({2,1}) == neigbours.end());
}

TEST_F(InfiniteBoardTestFixture, testGetDeadCells) {
    Cells deadCells = getDeadCells();
    EXPECT_EQ(deadCells.size(), 12);

    EXPECT_TRUE(deadCells.find({0,0}) != deadCells.end());
    EXPECT_TRUE(deadCells.find({10,10}) == deadCells.end());

    EXPECT_TRUE(deadCells.find({1,1}) == deadCells.end());
    EXPECT_TRUE(deadCells.find({1,2}) == deadCells.end());
    EXPECT_TRUE(deadCells.find({2,2}) == deadCells.end());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
