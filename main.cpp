#include <iostream>
#include <curses.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cerrno>

#include "point.h"
#include "Controller.h"
#include <unistd.h>

using namespace std;



int main()
{
    system("cd");
    Controller gCtl;

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, true);

    gCtl.updateScreen();

    for(;;){
        gCtl.getParseUserInput();
        gCtl.processCtlCall();
        gCtl.updateScreen();
        usleep(33333);
    }

    system("pause");
    return 0;
}
