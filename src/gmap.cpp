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

gmap::gmap()
{
    this->m_name = "NULL";

    m_size.Set_x(1);
    m_size.Set_y(1);

    m_data = Array2D<char>(m_size);
    m_data_state = Array2D<char>(m_size);
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

        m_data = Array2D<char>(m_size, root["Floor"].asString());
        m_data_state = Array2D<char>(m_size, root["State"].asString());

        for(int i = 0; i < root["Blocks"].size(); i++){
            blocks.insert(root["Blocks"][i].asString()[0]);
        }

        for(int i = 0; i < root["Objects"].size(); i++){
            Point cord(root["Objects"][i]["x"].asInt(), root["Objects"][i]["y"].asInt());
            mapObject toAdd(root["Objects"][i]["Name"].asString(), i, root["Objects"][i]["Type"].asInt(), cord.m_x, cord.m_y, root["Objects"][i]["Icon"].asString()[0], root["Objects"][i]["Trigger"].asString(), root["Objects"][i]["canStep"].asInt(), root["Objects"][i]["trigType"].asInt());
            objects.insert(objects.begin(),std::pair<Point,mapObject>(cord, toAdd));
        }

    }else{
        std::cout  << "Failed to parse configuration\n"  << reader.getFormatedErrorMessages();
        exit(128);
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

    objects = other.objects;
}

gmap& gmap::operator=(const gmap& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
        m_name = rhs.m_name;
        m_size = rhs.m_size;

        m_data = rhs.m_data;
        m_data_state = rhs.m_data_state;

        blocks = rhs.blocks;
        objects = rhs.objects;
    return *this;
}

bool gmap::isObstacle(Point a){
    if(blocks.find(m_data[a.m_y][a.m_x]) != blocks.end())
        return true;
    if(objects.find(a) != objects.end())
        if(!objects.find(a)->second.canStepOn())
            return true;
    return false;
}

bool gmap::isOutOfBound(Point a){
    if(a.m_x >= m_size.m_x || a.m_y >= m_size.m_y)
        return true;
    return false;
}

mapObject* gmap::getObject(Point a){
    if(objects.find(a) != objects.end())
        return &(objects[a]);
    return NULL;
}


