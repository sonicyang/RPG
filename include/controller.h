#include <map>
#include "gmap.h"
#include <string>
#include <curses.h>
#include "render.h"
#include "mapcontroller.h"
#include "eventcontroller.h"
#include "mapobject.h"
#include "objPlayer.h"
#include <deque>
#include "utils.h"

using namespace std;

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
    public:
        Controller();
        ~Controller();

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
