#include <map>
#include "gmap.h"
#include <string>
#include <curses.h>
#include "render.h"
#include "mapobject.h"

using namespace std;

#ifndef CONTROLLER_H
#define CONTROLLER_H


class Controller
{
    public:
        Controller(char* maplist);
        ~Controller();

        gmap get_CurrentMap();

        void updateScreen();
        void waitUserCommand();
    protected:
    private:
        render rdr;

        std::map<std::string,gmap> map_list;
        int map_count;
        string default_map;
        string current_map;
};

#endif // CONTROLLER_H
