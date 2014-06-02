#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <string>
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
#include "skillmenu.h"
#include "vender.h"
#include "startmenu.h"
#include "helpmenu.h"

using namespace std;

class mapController;

class Engine
{
    public:
        Engine();
        ~Engine();

        void excute();
        void excute(genericContorller&);
        void parseUserInput(genericContorller&);
        variant<paraVarType> engineCall(std::vector< variant<paraVarType> > );

    protected:
    private:
        int stop = 0;
        int fullstop = 0;
        
        render rdr;

        std::map< std::string, variant<paraVarType> > varMap;

        std::vector<genericContorller*> controllerStack;
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
        SkillMenu skillmenu;
        Vender vendor;
        StartMenu startmenu;
        HelpMenu helpmenu;

        void setStat(int s);
};

#endif // CONTROLLER_H
