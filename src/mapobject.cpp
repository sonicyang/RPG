#include "mapobject.h"
#include <string>
#include <cstdlib>
#include "utils.h"
#include "json/value.h"
#include "json/reader.h"

mapObject::mapObject() : name("NULL"), ID(0), type(0), icon('M'), _canStep(false)
{
    Cord.m_x = 0;
    Cord.m_y = 0;
}

mapObject::mapObject(std::string n, int i, int t, int x, int y, char ic, std::string trig, bool cs) : name(n), ID(i), type(t), icon(ic), _canStep(cs)
{
    Cord.m_x = x;
    Cord.m_y = y;
    if(trig != ""){
        std::string in = get_file_contents(trig.c_str());

        Json::Value root;
        Json::Reader reader;
        if (reader.parse( in, root )){

            trigger.stk.resize(root["Command"].size());
            for(int i = 0; i < root["Command"].size(); i++){
                trigger.stk[i] = root["Command"][i].asString();
            }

            trigger.trigBy = name;

            trigger.triggerType = root["triggerType"].asInt();
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
    _canStep = other._canStep;
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
        _canStep = rhs._canStep;
    return *this;
}


