#include <iostream>
#include <curses.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cerrno>

#include "point.h"
#include "Controller.h"

#include <windows.h>

using namespace std;



int main()
{
    system("cd");
    Controller gCtl("data/maps/maplist.lst");

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, true);

    gCtl.updateScreen();

    for(;;){
        gCtl.getParseUserInput();
        Sleep(33);
        gCtl.updateScreen();
    }

    system("pause");
    return 0;
}
