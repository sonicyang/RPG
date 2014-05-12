#include "controller.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include "gmap.h"
#include "point.h"
#include "utils.h"
#include "json/reader.h"
#include "json/value.h"
#include <string>
#include <curses.h>
#include "render.h"
#include <algorithm>

Controller::Controller() : rdr(), mapCtl("data/maps/maplist.lst", ctlCall), evtCtl(ctlCall)
{
}

Controller::~Controller()
{
}

void Controller::getParseUserInput(){
    int c = getch();
    switch(stat){
        case onMap:
            mapCtl.processInput(c);
            break;
        case inEvent:
            if(userInputPending){
                evtCtl.processInput(c);
            }else{
                evtCtl.execCurrentEvent();
            }
            break;
    }
}

bool Controller::processCtlCall(){
    if(ctlCall.size() == 0)
        return 1;
    int commd = *(int*)(ctlCall[0]);
    switch(commd){
        case -1:
            mapCtl.getPlayerFacingObject().getTrigger();
            evtCtl.reversePushEventStack(*(event*)(ctlCall[1]));
            this->setStat(inEvent);
            evtCtl.execCurrentEvent();
            userInputPending = 0;
            return 1;
        case 0:
            evtCtl.popEventStack();
            this->restoreStat();
            userInputPending = 0;
            return 0;
        case 1:
            prom.loadMessaage((char*)(ctlCall[1]), (char*)(ctlCall[2]));
            userInputPending = 1;
            return 1;
        case 2:
            prom.discardMessage();
            userInputPending = 0;
            return 0;
        case 255:
            for(int i = 0; i < ctlCall.size(); i++) //nasty memory Management :(
                delete [] ctlCall[i];
            exit(1);
            return 0;
    }

    for(int i = 0; i < ctlCall.size(); i++)
        delete [] ctlCall[i];

    ctlCall.clear();
    return 1;
}

void Controller::updateScreen(){
    rdr.render_map(mapCtl.getCurrentMap());
    rdr.render_Player(mapCtl.getPlayer());
    if(prom.hasMessage()){
        rdr.render_prompt(prom);
    }

    rdr.update();
    return;
}

void Controller::setStat(int s){
    _stat.push_back(stat);
    stat = s;
    return;
}

void Controller::restoreStat(){
    if(_stat.size() > 0){
        stat = _stat.back();
        _stat.pop_back();
    }
    return;
}

