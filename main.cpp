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

void help(){
    clear();

    //Make Frame and Print Title
    mvaddstr(0, 0, "================================================================================");
    for(int i = 1; i < 24; i++)mvaddch(i, 0, '|'),mvaddch(i, 79, '|');
    mvaddstr(24, 0, "===============================================================================");
    mvaddstr(2, 0, "================================================================================");

    //Print Title
    mvaddstr(1, 38, "HELP");

    mvaddstr(4, 2, "This is a Mini RPG Game");

    mvaddstr(8, 2, "Key Mapping:");
    mvaddstr(10, 2, "\t z - Select");
    mvaddstr(12, 2, "\t x - Cancel");
    mvaddstr(14, 2, "\t q - Menu");
    mvaddstr(16, 2, "\t Arrow Keys - Move");

    getch();
}

void startMenu(){
    std::vector<std::string> mOption(3);
    mOption[0] = "Start";
    mOption[1] = "Help/KeyMap";
    mOption[2] = "Exit";

    int cursorPos = 0;

    for(;;){
        clear();

        //Print All Options
        for(int i = 0; i < mOption.size(); i++)
        	mvaddstr(16 + 2*i, 40 - mOption[i].size()/2, mOption[i].c_str());

        //Print Selected Options
        attron(A_BOLD);
        mvaddstr(16 + 2*cursorPos, 40 - mOption[cursorPos].size()/2, mOption[cursorPos].c_str());
        attroff(A_BOLD);

        //Wait User input
        int c = getch();
        switch (c) {
            case KEY_UP:
                (cursorPos==0)? 0 : cursorPos--;
                break;
            case KEY_DOWN:
                (cursorPos == mOption.size()-1)? mOption.size()-1 : cursorPos++;
                break;
            case 'z':
            case KEY_ENTER:
                switch(cursorPos){
                    case 0:
                        return;
                        break;
                    case 1:
                        help();
                        break;
                    case 2:
                        exit(1);
                        break;
                }
                break;
        }
    }
    return;
}


int main()
{
    Controller gCtl;
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    startMenu();

    nodelay(stdscr, true);
    gCtl.updateScreen();

    for(;;){
        gCtl.getParseUserInput();
        if(!gCtl.processCtlCall())
        	break;
        gCtl.updateScreen();
        usleep(33333);
    }

    //system("pause");
    return 0;
}
