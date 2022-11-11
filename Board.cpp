#include "Board.h"

Board::Board(int tempWidth, int tempHeight) {
    width = tempWidth > 99 ? 99 : tempWidth;
    height = tempHeight > 99 ? 99 : tempHeight;
    charWidth = 2 * width + 1;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            resetString += "..";
        }
        resetString.push_back('\n');
    }
    boardString = resetString;
}

std::string Board::getBoardString() {
    return boardString;
}

void Board::testPrint() {
    std::cout << "  ";
    for (int i = 0; i < width; ++i) {
        std::string iToString = std::to_string(i);
        std::cout << (iToString.length() == 1 ? "0" + iToString : iToString);
    }
    std::vector<std::vector<std::string>> tempGrid{};
    int pos;
    for (int y = 0; y < height; ++y) {
        std::string yToString = std::to_string(y);
        std::cout << "\n" << (yToString.length() == 1 ? "0" + yToString : yToString);
        for (int x = 0; x < width; ++x) {
            pos = x * 2 + charWidth * y;
            std::cout << boardString[pos] << boardString[pos + 1];
        }
    }
    std::cout << "\n";
}
void Board::setTile(int tempX, int tempY, const std::string& s) {
    int pos = tempX * 2 + charWidth * tempY;
    boardString[pos] = s[0];
    boardString[pos + 1] = s[1];
}

void Board::setTile(std::pair<int, int> tempCoord, std::string s) {
    int pos = tempCoord.first * 2 + charWidth * tempCoord.second;
    boardString[pos] = s[0];
    boardString[pos + 1] = s[1];
}

void Board::setTiles(const std::vector<std::pair<int, int>>& coords, const std::string& s) {
    for (auto& coord : coords) {
        setTile(coord.first, coord.second, s);
    }
}

void Board::reset() {
    boardString = resetString;
}