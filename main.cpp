#include <iostream>
#include <curses.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cerrno>
#include "json/reader.h"
#include "json/value.h"

#include "point.h"
#include "gmap.h"
#include "Controller.h"

using namespace std;



int main()
{

    Controller gCtl("data/maps/maplist.lst");

    for(;;){
        int c = getch();
        switch (c) {
            case KEY_LEFT:
                gCtl.movePlayer(Point(-1,0));
                break;
            case KEY_RIGHT:
                gCtl.movePlayer(Point(1,0));
                break;
            case KEY_UP:
                gCtl.movePlayer(Point(0,-1));
                break;
            case KEY_DOWN:
                gCtl.movePlayer(Point(0,1));
                break;
            case 'z':

                break;
            case 'x':

                break;
            case KEY_END:
                return 0;
        }
    }

    system("pause");
    return 0;
}
