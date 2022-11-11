#include "Snake.h"

Snake::Snake(int width,
             int height,
             int tempLength,
             int tempDirection,
             std::pair<int, int> tempPos) {

    if (tempLength < 0)
        throw std::invalid_argument("tempLength cannot be negative");

    if (tempDirection < 0 || tempDirection > 3)
        throw std::invalid_argument("tempDirection is an invalid value");

    length = tempLength;
    direction = tempDirection;

    std::pair<int, int> positionChange;

    switch (tempDirection) {
        case 0  : positionChange = {0, 1} ; break;
        case 1  : positionChange = {-1, 0}; break;
        case 2  : positionChange = {0, -1}; break;
        case 3  : positionChange = {1, 0} ; break;
        default : positionChange = {0, 1} ; break;
    }

    int testX = tempPos.first  + positionChange.first  * tempLength;
    int testY = tempPos.second + positionChange.second * tempLength;

    if (testX < 0 || testX > width || testY < 0 || testY > height) {
        throw std::invalid_argument("snake segment positions out of bounds");
    }

    for (int i = 0; i < length; i++) {
        segmentPositions.push_back(tempPos);
        tempPos.first  += positionChange.first;
        tempPos.second += positionChange.second;
    }
}

int Snake::getLength() const {
    return length;
}

std::vector<std::pair<int, int>> Snake::getSegmentPositions() {
    return segmentPositions;
}

std::pair<int, int> Snake::getFirstPosition() {
    return segmentPositions[0];
}

void Snake::changeDirection(int tempDirection) {
    if (tempDirection < 0 || tempDirection > 3)
        throw std::invalid_argument("tempDirection is an invalid value");
    direction = tempDirection;
}

bool Snake::isAlive(int width, int height) {
    std::pair<int, int> firstPos = segmentPositions.front();
    if (length >= width * height)
        return false;
    //dead if head of snake is out of bounds
    if (firstPos.first < 0 || firstPos.second < 0 || firstPos.first >= width || firstPos.second >= height)
        return false;
    //dead if head is in the rest of the snake
    for (int i = 1; i < segmentPositions.size() - 1; ++i) {
        if (segmentPositions[i] == firstPos) {
            return false;
        }
    }
    return true;
}

void Snake::move() {
    std::pair <int, int> positionChange;
    switch (direction) {
        case 0  : positionChange = {0, -1}; break;
        case 1  : positionChange = {1, 0} ; break;
        case 2  : positionChange = {0, 1} ; break;
        case 3  : positionChange = {-1, 0}; break;
        default : positionChange = {0, -1}; break;
    }
    std::pair <int, int> newPosition = {segmentPositions[0].first  + positionChange.first,
                                        segmentPositions[0].second + positionChange.second};
    segmentPositions.push_back(newPosition);
    std::rotate(segmentPositions.rbegin(), segmentPositions.rbegin() + 1, segmentPositions.rend());
}

void Snake::moveSnake() {
    move();
    segmentPositions.pop_back();
}

void Snake::moveExtendSnake() {
    move();
    length++;
}