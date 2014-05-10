#include <map>
#include "gmap.h"
#include <string>
#include <curses.h>
#include "render.h"
#include "mapobject.h"
#include "objPlayer.h"

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

        int movePlayer(Point a);
    protected:
    private:
        render rdr;

        std::map<std::string,gmap> map_list;
        int map_count;
        string default_map;
        string current_map;

        objPlayer Player;
};

#endif // CONTROLLER_H
