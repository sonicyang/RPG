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
#include "chararray2d.h"
#include "mapobject.h"

gmap::gmap() : Player("Player", 0, 0, 0, 0, "^>v<", 0)
{
    this->m_name = "NULL";

    m_size.Set_x(1);
    m_size.Set_y(1);

    m_data = CharArray2D(m_size);
    m_data_state = CharArray2D(m_size);
}



gmap::gmap(const char * filename)
{
    std::string in = get_file_contents(filename);

    Json::Value root;
    Json::Reader reader;
    bool stat = reader.parse( in, root );
    if (stat){
        this->m_name = root.get("Name", "NULL" ).asString();

        m_size.Set_x(root["Size"]["x"].asInt());
        m_size.Set_y(root["Size"]["y"].asInt());

        m_data = CharArray2D(m_size, root["Floor"].asString());
        m_data_state = CharArray2D(m_size, root["State"].asString());

        for(int i = 0; i < root["Blocks"].size(); i++){
            blocks.insert(root["Blocks"][i].asString()[0]);
        }

        Player = mapObject("Player", 0, 0, root["Player"]["x"].asInt(), root["Player"]["y"].asInt(), "^>v<", EAST);

    }else{
        std::cout  << "Failed to parse configuration\n"  << reader.getFormatedErrorMessages();
    }
}

gmap::~gmap()
{
}

gmap::gmap(const gmap& other)
{
    m_name = other.m_name;
    m_size = other.m_size;

    m_data = other.m_data;
    m_data_state = other.m_data_state;

    blocks = other.blocks;

    Player = other.Player;
}

gmap& gmap::operator=(const gmap& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
        m_name = rhs.m_name;
        m_size = rhs.m_size;

        m_data = rhs.m_data;
        m_data_state = rhs.m_data_state;

        blocks = rhs.blocks;

        Player = rhs.Player;
    return *this;
}

const mapObject& gmap::getPlayer(){
    return Player;
}

int gmap::setPlayerPos(Point a){
    if(a.m_x >= m_size.m_x || a.m_y >= m_size.m_y || a.m_y < 0 || a.m_x < 0)
        return -1;
    if(isObstacle(a))
        return -1;
    Player.SetCord(a);
}

int gmap::movePlayer(Point a){
    Point curr = Player.GetCord();
    if(a.m_y != 0)
        Player.setFaceing(a.m_y + 1);
    else
        Player.setFaceing(a.m_x * -1 + 2);
    return setPlayerPos(curr + a);
}

Point gmap::getPlayerPos(){
    return Player.GetCord();
}

bool gmap::isObstacle(Point a){
    if(blocks.find(m_data[a.m_y][a.m_x]) != blocks.end())
        return true;
    return false;
}

bool gmap::isPlayerFacingObject(){

}


