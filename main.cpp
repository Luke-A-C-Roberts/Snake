#include "Board.h"
#include "Snake.h"
#include "Apple.h"
#include <unistd.h>
#include <ncurses.h>
#include <iostream>

#define WIDTH 40
#define HEIGHT 20

int main() {
    //main objects used for the game
    Board b(WIDTH, HEIGHT);
    Snake s(WIDTH, HEIGHT, 3, 1, {20, 10});
    Apple a(WIDTH, HEIGHT, s.getSegmentPositions());

    initscr();
    nodelay(stdscr, true);

    int delay;
    std::string choiceMessage {"enter nums 0 - 6 for snake speed\n"
                               "0 = slowest\n"
                               "6 = quickest"};
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
            case '5': delay = 93750; delayChoiceLoop = false; break;
            case '6': delay = 62500; delayChoiceLoop = false; break;
            default : break;
        }
        usleep(125000);
    }

    bool gameLoop = true;
    while (true) {
        //input
        switch (int ch = getch()) {
            case 'x': gameLoop = false; break;
            case 'w': s.changeDirection(0); break;
            case 'd': s.changeDirection(1); break;
            case 's': s.changeDirection(2); break;
            case 'a': s.changeDirection(3); break;
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
        gameLoop = s.isAlive(WIDTH, HEIGHT);
        if (!gameLoop) {break;}

        //update board
        b.reset();
        b.setTile(a.getPos(), "()");
        b.setTiles(s.getSegmentPositions(), "##");

        //rendering
        clear();
        printw("%d\n", s.getLength() - 3);
        printw("%s", b.getBoardString().c_str());
        usleep(delay);
    }

    sleep(2);
    endwin();
    std::cout << "snake score: " << s.getLength() - 3 << std::endl;
    return 0;
}
