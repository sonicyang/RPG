#include <string>
#include "point.h"
#include "eventcontroller.h"
#include <vector>
#include "utils.h"

#ifndef MAPOBJECT_H
#define MAPOBJECT_H

class mapObject
{
    public:
        friend class gmap;
        friend class mapController;

        mapObject();
        mapObject(std::string, int, int, int, int, char, std::string, bool, int);
        virtual ~mapObject();
        mapObject(const mapObject& other);
        mapObject& operator=(const mapObject& other);

        Point GetCord() { return Cord; }
        std::string Getname() { return name; }
        int GetID() { return ID; }
        int Gettype() { return type; }
        bool canStepOn() { return _canStep; }

        virtual char Geticon() const { return icon; }

        int getTriggerType() { return triggerType; };
        std::string getTrigger() { return trigger; };
    protected:
        Point Cord;
        void SetCord(Point val) { Cord = val; }
    private:

        std::string name;
        int ID;
        int type;
        char icon;
        bool _canStep;
        std::string trigger;
        int triggerType;
};

#endif // MAPOBJECT_H
