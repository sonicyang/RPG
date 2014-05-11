#include <iostream>
#include <curses.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cerrno>

#include "point.h"
#include "Controller.h"

using namespace std;



int main()
{
    system("cd");
    Controller gCtl("data/maps/maplist.lst");

    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    gCtl.updateScreen();

    for(;;){
        int c = getch();
        switch (c) {
            case KEY_LEFT:
                gCtl.move(Point(-1,0));
                break;
            case KEY_RIGHT:
                gCtl.move(Point(1,0));
                break;
            case KEY_UP:
                gCtl.move(Point(0,-1));
                break;
            case KEY_DOWN:
                gCtl.move(Point(0,1));
                break;
            case 'z':
                gCtl.trigger();
                break;
            case 'x':
                gCtl.esc();
                break;
            case KEY_END:
                return 0;
        }

        gCtl.updateScreen();
    }

    system("pause");
    return 0;
}
