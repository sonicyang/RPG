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
        void loadEventStack(std::vector<std::string>);
        void execEvent(std::string);

        int getStat() { return stat; };

    protected:
    private:
        render rdr;

        std::map<std::string,gmap> map_list;
        int map_count;
        string default_map;
        string current_map;

        objPlayer Player;

        std::vector<std::string> eventStack;

        std::string prompt;

        int stat = 1;
};

#endif // CONTROLLER_H
