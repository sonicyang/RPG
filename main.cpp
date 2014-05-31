#include <iostream>
#include <curses.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cerrno>

#include "point.h"
#include "engine.h"
#include <unistd.h>
#include <locale.h>

//For the sake of NcursesW
#define _XOPEN_SOURCE_EXTENDED

using namespace std;

int main()
{
    Engine gCtl;
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, TRUE);
    gCtl.excute();
    endwin();
    return 0;
}
