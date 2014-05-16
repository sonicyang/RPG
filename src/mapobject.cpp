#include <string>
#include <cstdlib>
#include "json/value.h"
#include "json/reader.h"
#include "utils.h"
#include "mapobject.h"

mapObject::mapObject() : name("NULL"), ID(0), type(0), icon('M'), _canStep(false), triggerType(0)
{
    Cord.m_x = 0;
    Cord.m_y = 0;
}

mapObject::mapObject(std::string n, int i, int t, int x, int y, wchar_t ic, std::string trig, bool cs, int trigType) : name(n), ID(i), type(t), icon(ic), _canStep(cs), trigger(trig), triggerType(trigType)
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
    trigger = other.trigger;
    _canStep = other._canStep;
    triggerType = other.triggerType;
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
        triggerType = rhs.triggerType;
    return *this;
}


