#include "point.h"
#include <string>
#include <set>
#include <map>
#include "mapobject.h"
#include "chararray2d.h"

#ifndef GMAP_H
#define GMAP_H


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

        Array2D<char> Getdata() { return m_data; }

        bool isObstacle(Point);
        bool isOutOfBound(Point);

        bool isPlayerFacingObject();

        mapObject* getObject(Point);
        const std::map<Point,mapObject>& getObjects() { return objects; };

    protected:
    private:
        Point m_size;
        std::string m_name;
        Array2D<char> m_data;
        Array2D<char> m_data_state;
        std::set<char> blocks;

        std::map<Point,mapObject> objects;
};

#endif // GMAP_H
