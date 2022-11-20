#include "Board.h"

/// @brief creates the board of width and height specified
/// @param tempWidth 
/// @param tempHeight 
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

/// @brief returns board as a string
/// @return std::string
const std::string& Board::getBoardString() {
    return boardString;
}

/// @brief prints board for debug
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

/// @brief sets a board pixle at a specific x and y
/// @param tempX int, 0 <= x < width
/// @param tempY int, 0 <= y < height
/// @param s std::string (length = 2)
void Board::setTile(int tempX, int tempY, const std::string& s) {
    if (tempX < 0 || tempX >= width || tempY < 0 || tempY >= height)
        return;
    if (s.length() != 2)
        return;
    int pos = tempX * 2 + charWidth * tempY;
    boardString[pos] = s[0];
    boardString[pos + 1] = s[1];
}

/// @brief sets a board pixle at a specific coordinet
/// @param tempCoord std::pair<int, int> {0 <= x < width, 0 <= y < height}
/// @param s 
void Board::setTile(std::pair<int, int> tempCoord, std::string s) {
    if (tempCoord.first < 0 || tempCoord.first >= width || tempCoord.second < 0 || tempCoord.second >= height)
        return;
    if (s.length() != 2)
        return;
    int pos = tempCoord.first * 2 + charWidth * tempCoord.second;
    boardString[pos] = s[0];
    boardString[pos + 1] = s[1];
}

/// @brief sets a board pixles at a specific set of coordinates
/// @param coords const std::vector<std::pair<int, int>>& {{x0, y0}, {x1, y1},..., {xn, yn}} where 0 <= x < width and 0 <= y < height
/// @param s 
void Board::setTiles(const std::vector<std::pair<int, int>>& coords, const std::string& s) {
    for (auto& coord : coords) {
        setTile(coord.first, coord.second, s);
    }
}

void Board::reset() {
    boardString = resetString;
}
