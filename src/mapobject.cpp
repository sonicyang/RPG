#include "mapobject.h"
#include <string>

mapObject::mapObject() : name("NULL"), ID(0), type(0), icon("^>v<"), facing(SOUTH)
{
    Cord.m_x = 0;
    Cord.m_y = 0;
}

mapObject::mapObject(std::string n, int i, int t, int x, int y, std::string ic, int f) : name(n), ID(i), type(t), icon(ic), facing(f)
{
    Cord.m_x = x;
    Cord.m_y = y;
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
    facing = other.facing;
}

mapObject& mapObject::operator=(const mapObject& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
        name = rhs.name;
        type = rhs.type;
        ID = rhs.ID;
        Cord = rhs.Cord;
        icon = rhs.icon;
        facing = rhs.facing;
    return *this;
}

void mapObject::setFaceing(int f){
    if(f < 0 || f > 3)
        return;
    facing = f;
    return;
}
