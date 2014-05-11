#include "mapobject.h"
#include <string>
#include <cstdlib>
#include "utils.h"
#include "json/value.h"
#include "json/reader.h"

mapObject::mapObject() : name("NULL"), ID(0), type(0), icon('M'), trigger(NULL)
{
    Cord.m_x = 0;
    Cord.m_y = 0;
}

mapObject::mapObject(std::string n, int i, int t, int x, int y, char ic, std::string trig) : name(n), ID(i), type(t), icon(ic)
{
    Cord.m_x = x;
    Cord.m_y = y;
    if(trig != ""){
        std::string in = get_file_contents(trig.c_str());

        Json::Value root;
        Json::Reader reader;
        if (reader.parse( in, root )){
            trigger.resize(root["Command"].size());
            for(int i = 0; i < root["Command"].size(); i++){
                trigger[i] = root["Command"][i].asString();
            }

        }else{
            std::cout << "Failed to parse configuration\n"  << reader.getFormatedErrorMessages();
            exit(128);
        }
    }
}

mapObject::~mapObject()
{
}

mapObject::mapObject(const mapObject& other)
{
    name = other.name;
    type = other.type;
    ID = other.ID;
    Cord = other.Cord;
    icon = other.icon;
    trigger = other.trigger;
}

mapObject& mapObject::operator=(const mapObject& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
        name = rhs.name;
        type = rhs.type;
        ID = rhs.ID;
        Cord = rhs.Cord;
        icon = rhs.icon;
        trigger = rhs.trigger;
    return *this;
}


