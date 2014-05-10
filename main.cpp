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

    do{
        gCtl.waitUserCommand();
        gCtl.updateScreen();
    }while(1);

    system("pause");
    return 0;
}
