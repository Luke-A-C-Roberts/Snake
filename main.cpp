#include "Board.h"
#include "Snake.h"
#include "Apple.h"
#include <unistd.h>
#include <ncurses.h>
#include <iostream>
#include <algorithm>

#define WIDTH 40
#define HEIGHT 20

bool doGame() {
    bool continueGame;
    std::string choiceMessage {"Do you want to play (again) [y/n]?\n"};
    bool gameChoiceLoop = true;
    while(gameChoiceLoop) {
        clear();
        printw("%s", choiceMessage.c_str());
        switch (int ch = getch()) {
            case 'y': continueGame = true; gameChoiceLoop = false; break;
            case 'n': continueGame = false; gameChoiceLoop = false; break;
            default : break;
        }
        usleep(125000);
    }
    return continueGame;
}

int choseDelay() {
    int delay;
    std::string choiceMessage {"controls:\n\tuse WASD for direction or press X to exit\n\nenter nums 0 - 6 for snake speed\n0 = slowest\n6 = quickest\n"};
    bool delayChoiceLoop = true;
    while(delayChoiceLoop) {
        clear();
        printw("%s", choiceMessage.c_str());
        switch (int ch = getch()) {
            case '0': delay = 500000; delayChoiceLoop = false; break;
            case '1': delay = 375000; delayChoiceLoop = false; break;
            case '2': delay = 250000; delayChoiceLoop = false; break;
            case '3': delay = 187500; delayChoiceLoop = false; break;
            case '4': delay = 125000; delayChoiceLoop = false; break;
            case '5': delay = 93750;  delayChoiceLoop = false; break;
            case '6': delay = 62500;  delayChoiceLoop = false; break;
            default : break;
        }
        usleep(125000);
    }
    return delay;
}

int playGame(int delay) {
    //main objects used for the game
    Board b(WIDTH, HEIGHT);
    Snake s(WIDTH, HEIGHT, 3, 1, {20, 10});
    Apple a(WIDTH, HEIGHT, s.getSegmentPositions());

    bool gameLoop = true;
    //gameloop (every cycle the snake moves forward 1 step)
    while (true) {
        //input
        switch (int ch = getch()) {
            case 'x': gameLoop = false; break;
            case 'w': s.changeDirection(0); break;
            case 'd': s.changeDirection(1); break;
            case 's': s.changeDirection(2); break;
            case 'a': s.changeDirection(3); break;
            case KEY_UP   : s.changeDirection(0); break;
            case KEY_RIGHT: s.changeDirection(1); break;
            case KEY_DOWN : s.changeDirection(2); break;
            case KEY_LEFT : s.changeDirection(3); break;
            default : break;
        }

        //positions
        if (s.getFirstPosition() == a.getPos()) {
            s.moveExtendSnake();
            a.randomPos(WIDTH, HEIGHT, s.getSegmentPositions());
        }
        else {
            s.moveSnake();
        }

        //continue the game loop?
        gameLoop = s.isAlive(WIDTH, HEIGHT)&&gameLoop;
        if (!gameLoop) {break;}

        //update board
        b.reset();
        b.setTile(a.getPos(), "()");
        b.setTiles(s.getSegmentPositions(), "##");
        std::string snakeHead;
        switch (s.getDirection()) {
            case 0: snakeHead = "/\\"; break;
            case 1: snakeHead = "|>";  break;
            case 2: snakeHead = "\\/"; break;
            case 3: snakeHead = "<|";  break;
        }
        b.setTile(s.getFirstPosition(), snakeHead);

        //rendering
        clear();
        printw("%d\n", s.getLength() - 3);
        printw("%s", b.getBoardString().c_str());
        usleep(delay);
    }
    return s.getLength() - 3;
}

int main() {

    //initialises the ncurses screen with no keyboard input buffer delay 
    initscr();
    nodelay(stdscr, true);
    keypad(stdscr, true);

    //keeps track of the game num and score
    std::vector<std::pair<int, int>> games;
    int game = 1;
    while (doGame()) {
        //allows the user to select a speed to play
        int delay = choseDelay();
        //game
        games.push_back({playGame(delay), game});
        game++;
        sleep(2);
    }
    endwin();

    //sort and reverse the scores
    std::sort(games.begin(), games.end());
    std::reverse(games.begin(), games.end());

    std::cout << "_________________\n|game\t|score\t|\n";
    for (auto& g : games) {
        std::cout << "|" << g.second << "\t|" << g.first << "\t|\n";
    }
    std::cout << std::endl;

    return 0;
}
