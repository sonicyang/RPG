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

        std::deque< std::vector< variant<int, unsigned int, char*, std::string> > > ctlCall;

        mapController mapCtl;
        eventController evtCtl;
        inventory inv;

        prompt prom;

        //battle currBattle;
        //vector<GeneralPlayer> members;

        void menuRutin();
        void invMenuRoutin();

        void setStat(int s);
        void restoreStat();
        int stat = 1;
        vector<int> _stat;
};

#endif // CONTROLLER_H
