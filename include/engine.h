#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <string>
#include <curses.h>
#include <deque>
#include "gmap.h"
#include "render.h"
#include "mapcontroller.h"
#include "eventcontroller.h"
#include "mapobject.h"
#include "objPlayer.h"
#include "inventory.h"
#include "utils.h"
#include "variant.h"
#include "team.h"
#include "rolefactory.h"
#include "role.h"

using namespace std;

class Engine
{
    public:
        Engine();
        ~Engine();

        void getParseUserInput();
        bool processCtlCall();
        void updateScreen();

        int getStat() { return stat; };
    protected:
    private:
        render rdr;

        std::deque< std::vector< variant<paraVarType> > > ctlCall;
        std::map< std::string, variant<paraVarType> > varMap;

        mapController mapCtl;
        eventController evtCtl;
        inventory inv;
        Team team;

        prompt prom;

        //battle currBattle;
        //vector<GeneralPlayer> members;

        void menuRutin();
        unsigned int invMenuRoutin(const int val = 0);
        unsigned int teamMenuRoutin(const int val = 0);

        void setStat(int s);
        void restoreStat();
        int stat = 1;
        vector<int> _stat;

        std::vector<std::string> mOption;
};

#endif // CONTROLLER_H
