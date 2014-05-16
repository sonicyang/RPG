#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <string>
#include <vector>
#include "eventcontroller.h"
#include "utils.h"
#include "point.h"

class mapObject
{
    public:
        friend class gmap;
        friend class mapController;

        mapObject();
        mapObject(std::string, int, int, int, int, wchar_t, std::string, bool, int);
        virtual ~mapObject();
        mapObject(const mapObject& other);
        mapObject& operator=(const mapObject& other);

        Point GetCord() { return Cord; }
        std::string Getname() { return name; }
        int GetID() { return ID; }
        int Gettype() { return type; }
        bool canStepOn() { return _canStep; }

        virtual wchar_t Geticon() const { return icon; }

        int getTriggerType() { return triggerType; };
        std::string getTrigger() { return trigger; };
    protected:
        Point Cord;
        void SetCord(Point val) { Cord = val; }
    private:

        std::string name;
        int ID;
        int type;
        wchar_t icon;
        bool _canStep;
        std::string trigger;
        int triggerType;
};

#endif // MAPOBJECT_H
