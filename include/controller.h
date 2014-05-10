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

enum Stats{
    onMap = 1,
    conversation,
    battle,
    menu
};

class Controller
{
    public:
        Controller(char* maplist);
        ~Controller();

        gmap get_CurrentMap();

        void updateScreen();

        void move(Point a);
        void trigger();
        void esc();

        int setPlayerPos(Point a);
        Point getPlayerPos();
        int movePlayer(Point a);

        int getStat() { return stat; };
    protected:
    private:
        render rdr;

        std::map<std::string,gmap> map_list;
        int map_count;
        string default_map;
        string current_map;

        objPlayer Player;

        int stat = 1;
};

#endif // CONTROLLER_H
