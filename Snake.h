#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

class Snake {
private:
    int length{};
    int direction{}; //0 = up, 1 = right, 2 = down, 3 = left
    std::vector<std::pair<int, int>> segmentPositions{};
    void move();
public:
    Snake(int, int, int, int, std::pair<int, int>);

    int getLength() const;
    std::vector<std::pair<int, int>> getSegmentPositions();
    std::pair<int, int> getFirstPosition();
    int getDirection();

    void changeDirection(int);
    void moveSnake();
    void moveExtendSnake();
    bool isAlive(int, int);
};

#endif //SNAKE_SNAKE_H
