#include <vector>
#include <random>
#include <iostream>

#ifndef SNAKE_APPLE_H
#define SNAKE_APPLE_H

class Apple {
private:
    std::pair<int, int> position;
public:
    Apple(int, int, const std::vector<std::pair<int, int>>&);
    std::pair<int,int> getPos();
    void randomPos(int, int, const std::vector<std::pair<int, int>>&);
    bool isEaten(std::pair<int, int>);
};

#endif //SNAKE_APPLE_H
