#include "mapcontroller.h"
#include "utils.h"
#include "json/reader.h"
#include "json/value.h"
#include <cstdlib>

mapController::mapController(char* maplist)
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
        defaultMap = currentMap = root["Default"].asString();

    }else{
        std::cout << "Failed to parse configuration\n"  << reader.getFormatedErrorMessages();
        exit(128);
    }

    player = objPlayer("Player", 0, 0, 1, 1, "^>v<", EAST);
}

mapController::~mapController()
{
    //dtor
}

const gmap& mapController::getCurrentMap(){
    return map_list[currentMap];
}

int mapController::setPlayerPosition(Point a){
    if(map_list[currentMap].isOutOfBound(a))
        return -1;
    if(map_list[currentMap].isObstacle(a))
        return -1;
    player.SetCord(a);
}

int mapController::movePlayer(Point a){
    Point curr = player.GetCord();
    if(a.m_y != 0)
        player.setFacing(a.m_y + 1);
    else
        player.setFacing(a.m_x * -1 + 2);
    return setPlayerPosition(curr + a);
}

Point mapController::getPlayerPosition(){
    return player.GetCord();
}

Point mapController::getPlayerFacing(){
    Point cordFacing = player.GetCord();
    switch(player.getFacing()){
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

bool mapController::isPlayerFacingObject(){
    mapObject* obj = map_list[currentMap].getObject(getPlayerFacing());
    if(!obj)
        return false;
    return true;
}

mapObject& mapController::getPlayerFacingObject(){
    return *map_list[currentMap].getObject(getPlayerFacing());
}
