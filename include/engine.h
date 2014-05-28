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
#include "battle.h"
#include "mainmenu.h"
#include "teammenu.h"
#include "invmenu.h"
#include "charmenu.h"

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

        Battle battle;

        MainMenu mainmenu;
        TeamMenu teammenu;
        InvMenu invmenu;
        CharMenu charmenu;

        void menuRutin();
        int invMenuRoutin(const int val = 0);
        int teamMenuRoutin(const int val = 0);
        int charMenuRoutin(const int val = 0, std::string cname = "");

        void setStat(int s);
        void restoreStat();
        int stat = 1;
        vector<int> _stat;
};

#endif // CONTROLLER_H
