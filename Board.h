#include <string>
#include <vector>
#include <iostream>
#include <ncurses.h>

#ifndef SNAKE_BOARD_H
#define SNAKE_BOARD_H

class Board {
private:
    int width;
    int height;
    int charWidth;
    std::string boardString{};
    std::string resetString{};
public:
    Board(int, int);
    std::string getBoardString();
    void testPrint();
    void setTile(int, int, const std::string&);
    void setTile(std::pair<int, int>, std::string);
    void setTiles(const std::vector<std::pair<int, int>>&, const std::string&);
    void reset();
};

#endif //SNAKE_BOARD_H
