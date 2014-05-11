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
    inEvent,
    menu
};

struct PROM{
    std::string whom;
    std::string prom;
};

class Controller
{
    public:
        Controller(char* maplist);
        ~Controller();

        gmap get_CurrentMap();

        void getParseUserInput();
        void updateScreen();

        int setPlayerPos(Point a);
        Point getPlayerPos();
        Point getPlayerFacing();
        int movePlayer(Point a);

        event getCurentMapObjectEvent(Point);
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
        //inv inventory;

        vector<event> eventStack;

        PROM prompt;

        //battle currBattle;
        //vector<GeneralPlayer> members;

        void setStat(int s);
        void restoreStat();
        int stat = 1;
        vector<int> _stat;
};

#endif // CONTROLLER_H
