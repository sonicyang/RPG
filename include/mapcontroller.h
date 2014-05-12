#include "gmap.h"
#include "mapObject.h"
#include "objPLayer.h"
#include "point.h"

#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H


class mapController
{
    public:
        mapController(char* maplist);
        ~mapController();

        const gmap& getCurrentMap();

        int setPlayerPosition(Point a);
        Point getPlayerPosition();
        int movePlayer(Point a);
        const objPlayer& getPlayer() { return player; }

        bool isPlayerFacingObject();
        mapObject& getPlayerFacingObject();

    protected:
    private:
        std::string currentMap;
        std::string defaultMap;
        std::map<std::string, gmap> map_list;
        int map_count;

        objPlayer player;

        Point getPlayerFacing();
};

#endif // MAPCONTROLLER_H
