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
#include "utils.h"

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
        std::deque< std::vector<void*> > ctlCall;

        render rdr;
        mapController mapCtl;
        eventController evtCtl;

        bool userInputPending = false;

        //inv inventory;

        prompt prom;

        //battle currBattle;
        //vector<GeneralPlayer> members;

        void menuRution();

        void setStat(int s);
        void restoreStat();
        int stat = 1;
        vector<int> _stat;
};

#endif // CONTROLLER_H
