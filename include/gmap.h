#ifndef GMAP_H
#define GMAP_H

#include <string>
#include <set>
#include <map>
#include "mapobject.h"
#include "array2d.h"
#include "point.h"

class gmap
{
    public:
        gmap();
        gmap(const char * filename);
        ~gmap();
        gmap(const gmap& other);
        gmap& operator=(const gmap& other);

        Point Getsize() { return m_size; }

        std::string Getname() { return m_name; }
        void Setname(std::string val) { m_name = val; }

        Array2D<wchar_t> Getdata() { return m_data; }

        bool isObstacle(Point);
        bool isOutOfBound(Point);

        bool isPlayerFacingObject();

        mapObject* getObject(Point);
        const std::map<Point,mapObject>& getObjects() { return objects; };

    protected:
    private:
        Point m_size;
        std::string m_name;
        Array2D<wchar_t> m_data;
        Array2D<wchar_t> m_data_state;
        std::set<wchar_t> blocks;

        std::map<Point, mapObject> objects;
};

#endif // GMAP_H
