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

Controller::Controller(char* maplist) : rdr()
{
    std::string in = get_file_contents(maplist);

    Json::Value root;
    Json::Reader reader;
    bool stat = reader.parse( in, root );
    if (stat){
        map_count = root.get("Count", 0 ).asInt();
        for(int i = 0; i < map_count; i++){
            gmap tmp(root["Path"][i].asString().c_str());
            map_list.insert (map_list.begin(), std::pair<std::string,gmap>(tmp.Getname(),tmp));
        }
        default_map = current_map = root["Default"].asString();

    }else{
        std::cout << "Failed to parse configuration\n"  << reader.getFormatedErrorMessages();
        exit(128);
    }

    Player = objPlayer("Player", 0, 0, 1, 1, "^>v<", EAST);
}

Controller::~Controller()
{
}

gmap Controller::get_CurrentMap(){
    return map_list[current_map];
}

void Controller::getParseUserInput(){
    int c = getch();
    switch(stat){
        case onMap:
            switch (c) {
                case KEY_LEFT:
                    movePlayer(Point(-1,0));
                    break;
                case KEY_RIGHT:
                    movePlayer(Point(1,0));
                    break;
                case KEY_UP:
                    movePlayer(Point(0,-1));
                    break;
                case KEY_DOWN:
                    movePlayer(Point(0,1));
                    break;
                case 'z':{
                    mapObject* obj = map_list[current_map].getObject(getPlayerFacing());
                    if(!obj)
                        return;
                    loadEventStack(obj->getTrigger());
                    execEvent();
                    break;}
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
    rdr.render_map(map_list[current_map]);
    rdr.render_Player(Player);
    if(stat == inEvent)
        rdr.render_prompt(prompt.prom, prompt.whom);
    rdr.update();
    return;
}

int Controller::setPlayerPos(Point a){
    if(map_list[current_map].isOutOfBound(a))
        return -1;
    if(map_list[current_map].isObstacle(a))
        return -1;
    Player.SetCord(a);
}

int Controller::movePlayer(Point a){
    Point curr = Player.GetCord();
    if(a.m_y != 0)
        Player.setFacing(a.m_y + 1);
    else
        Player.setFacing(a.m_x * -1 + 2);
    return setPlayerPos(curr + a);
}

Point Controller::getPlayerPos(){
    return Player.GetCord();
}

Point Controller::getPlayerFacing(){
    Point cordFacing = Player.GetCord();
    int facing = Player.getFacing();
    switch(facing){
        case 0:
            cordFacing += Point(0,-1);
            break;
        case 1:
            cordFacing += Point(1,0);
            break;
        case 2:
            cordFacing += Point(0,1);
            break;
        case 3:
            cordFacing += Point(-1,0);
            break;
    }
    return cordFacing;
}

void Controller::loadEventStack(event trig){
    std::reverse(trig.stk.begin(), trig.stk.end());
    setStat(trig.type);
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
    int s;
    switch(commd){
        /*case 0:
            s = atoi(ss[1].c_str());
            s = ((s == 0)? onMap : s);
            setStat(s);
            execEvent();
            return 0;*/ //Removed after implementing event type
        case 1:
            prompt.prom = ss[1];
            prompt.whom = eventStack.back().trigBy;
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

