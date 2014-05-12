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

Controller::Controller() : rdr(), mapCtl("data/maps/maplist.lst")
{
}

Controller::~Controller()
{
}

void Controller::getParseUserInput(){
    int c = getch();
    switch(stat){
        case onMap:
            switch (c) {
                case KEY_LEFT:
                    mapCtl.movePlayer(Point(-1,0));
                    break;
                case KEY_RIGHT:
                    mapCtl.movePlayer(Point(1,0));
                    break;
                case KEY_UP:
                    mapCtl.movePlayer(Point(0,-1));
                    break;
                case KEY_DOWN:
                    mapCtl.movePlayer(Point(0,1));
                    break;
                case 'z':
                    if(mapCtl.isPlayerFacingObject()){
                        loadEventStack(mapCtl.getPlayerFacingObject().getTrigger());
                        execEvent();
                    }
                    break;
                case KEY_END:
                    exit(1);
            }
            break;
        case inEvent:
            switch (c) {
                case KEY_LEFT:

                    break;
                case KEY_RIGHT:

                    break;
                case KEY_UP:

                    break;
                case KEY_DOWN:

                break;
                case 'z':
                    execEvent();
                    break;
                case 'x':
                    eventStack.back().stk.clear();
                    execEvent();
                    break;
                case KEY_END:
                    exit(1);
            }
            break;
    }
}

void Controller::updateScreen(){
    rdr.render_map(mapCtl.getCurrentMap());
    rdr.render_Player(mapCtl.getPlayer());
    if(stat == inEvent)
        rdr.render_prompt(prompt.prom, prompt.whom);
    rdr.update();
    return;
}

void Controller::loadEventStack(event trig){
    std::reverse(trig.stk.begin(), trig.stk.end());
    setStat(inEvent);
    eventStack.push_back(trig);
}

int Controller::execEvent(){
    if(eventStack.back().stk.size() == 0){
        restoreStat();
        eventStack.pop_back();
        return -1;
    }

    std::vector<std::string> ss = split(eventStack.back().stk.back(), '|');
    eventStack.back().stk.pop_back();

    int commd = atoi(ss[0].c_str());
    switch(commd){
        case 0:
            /*currBattle = battle(ss[1]);
            currBattle.exec();
            return 0;*/
        case 1:
            prompt.whom = ss[1];
            prompt.prom = ss[2];
            return 1;
    }

    return 1;
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

