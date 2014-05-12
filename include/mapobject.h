#include <string>
#include "point.h"
#include "eventcontroller.h"
#include <vector>

#ifndef MAPOBJECT_H
#define MAPOBJECT_H

enum faceing{
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
};

class mapObject
{
    public:
        friend class gmap;
        friend class mapController;

        mapObject();
        mapObject(std::string, int, int, int, int, char, std::string);
        ~mapObject();
        mapObject(const mapObject& other);
        mapObject& operator=(const mapObject& other);

        Point GetCord() { return Cord; }
        std::string Getname() { return name; }
        int GetID() { return ID; }
        int Gettype() { return type; }
        virtual char Geticon() const { return icon; }

        const event& getTrigger() const { return trigger; };
    protected:
        Point Cord;
        void SetCord(Point val) { Cord = val; }
    private:
        int ID;
        std::string name;
        int type;
        char icon;

        event trigger;

};

#endif // MAPOBJECT_H
