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

void Controller::updateScreen(){
    rdr.render_map(map_list[current_map]);
    rdr.render_Player(Player);
    if(stat == conversation)
        rdr.render_prompt(prompt);
    rdr.update();
    return;
}

void Controller::move(Point a){
    switch(stat){
        case onMap:
                movePlayer(a);
            break;
    }
}

void Controller::trigger(){
    switch(stat){
        case onMap:
                TriggerMapObject();
            break;
    }
}
void Controller::esc(){

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

void Controller::TriggerMapObject(){
    Point cordFacing = Player.GetCord();
    int facing = Player.getFacing();
    switch(stat){
        case 0:
            cordFacing += Point(-1,0);
            break;
        case 1:
            cordFacing += Point(0,1);
            break;
        case 2:
            cordFacing += Point(1,0);
            break;
        case 3:
            cordFacing += Point(0,-1);
            break;
    }

    mapObject* obj = map_list[current_map].getObject(cordFacing);
    if(!obj)
        return;

    eventStack = obj->getTrigger();


}

void Controller::loadEventStack(std::vector<std::string> trig){
    stat = pending;
}

void Controller::execEvent(std::string comm){
    std::vector<std::string> ss = split(comm, '|');
    int commd = atoi(ss[0].c_str());
    switch(commd){
        case 0:
            stat = atoi(ss[1].c_str());
            stat = (!stat)? onMap : stat;
            break;
        case 1:
            prompt = ss[1];
            break;
    }
    return;
}



