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
    pending = 0,
    onMap,
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

        void TriggerMapObject();
        void loadEventStack(event);
        int execEvent();

        int getStat() { return stat; };

    protected:
    private:
        render rdr;

        std::map<std::string,gmap> map_list;
        int map_count;
        string default_map;
        string current_map;

        objPlayer Player;

        event eventStack;

        std::string prompt;

        void setStat(int s);
        void restoreStat();
        int stat = 1;
        vector<int> _stat;
};

#endif // CONTROLLER_H
