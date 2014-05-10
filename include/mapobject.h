#include <string>
#include "point.h"

#ifndef MAPOBJECT_H
#define MAPOBJECT_H


class mapObject
{
    public:
        friend class gmap;

        mapObject();
        mapObject(std::string, int, int, int, int, char);
        ~mapObject();
        mapObject(const mapObject& other);
        mapObject& operator=(const mapObject& other);

        Point GetCord() { return Cord; }
        int GetID() { return ID; }
        int Gettype() { return type; }
        char Geticon() { return icon; }
    protected:
        Point Cord;
        void SetCord(Point val) { Cord = val; }
    private:
        int ID;
        std::string name;
        int type;
        char icon;
};

#endif // MAPOBJECT_H
