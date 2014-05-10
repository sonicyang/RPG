#include "mapobject.h"
#include <string>

mapObject::mapObject() : name("NULL"), ID(0), type(0), icon("M")
{
    Cord.m_x = 0;
    Cord.m_y = 0;
}

mapObject::mapObject(std::string n, int i, int t, int x, int y, char ic) : name(n), ID(i), type(t), icon(ic)
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
}

mapObject& mapObject::operator=(const mapObject& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
        name = rhs.name;
        type = rhs.type;
        ID = rhs.ID;
        Cord = rhs.Cord;
        icon = rhs.icon;
    return *this;
}


