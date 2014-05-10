#include <string>
#include "point.h"

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

        mapObject();
        mapObject(std::string, int, int, int, int, std::string, int);
        ~mapObject();
        mapObject(const mapObject& other);
        mapObject& operator=(const mapObject& other);

        Point GetCord() { return Cord; }
        int GetID() { return ID; }
        int Gettype() { return type; }
        char Geticon() { return icon[facing]; }
        int getFaceing() { return facing; }
        void setFaceing(int);
    protected:
        Point Cord;
        void SetCord(Point val) { Cord = val; }
    private:
        int ID;
        std::string name;
        int type;
        std::string icon;
        int facing;
};

#endif // MAPOBJECT_H
