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
        Player.setFaceing(a.m_y + 1);
    else
        Player.setFaceing(a.m_x * -1 + 2);
    return setPlayerPos(curr + a);
}

Point Controller::getPlayerPos(){
    return Player.GetCord();
}


