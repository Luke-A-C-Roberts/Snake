#include "Apple.h"

/// \param width the width of the board
/// \param height the height of the board
/// \param snakePos the positions of the snake segments
Apple::Apple(int width, int height, const std::vector<std::pair<int, int>>& snakePos) {
    std::srand(time(NULL));

    bool foundPos = false;
    std::pair<int, int> tempPos{};
    while (!foundPos) {
        tempPos = {std::rand() % width, std::rand() % height};
        foundPos = true;
        for (auto& coord : snakePos) {
            if (tempPos == coord) {
                foundPos = false;
                break;
            }
        }
    }
    position = tempPos;
}

std::pair<int, int> Apple::getPos() {
    return position;
}

/// \param width the width of the board
/// \param height the height of the board
/// \param snakePos the positions of the snake segments
void Apple::randomPos(int width, int height, const std::vector<std::pair<int, int>>& snakePos) {
    bool foundPos = false;
    std::pair<int, int> tempPos{};
    while (!foundPos) {
        tempPos = {std::rand() % width, std::rand() % height};
        foundPos = true;
        if (tempPos == position)
            continue;
        for (auto& coord : snakePos) {
            if (tempPos == coord) {
                foundPos = false;
                break;
            }
        }
    }
    position = tempPos;
}

bool Apple::isEaten(std::pair<int, int> snakeFront) {
    return position == snakeFront;
}
