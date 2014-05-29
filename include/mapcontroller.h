#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H

#include "gmap.h"
#include "mapobject.h"
#include "objplayer.h"
#include "variant.h"
#include "point.h"

class mapController
{
    public:
        mapController(std::string maplist, std::deque< std::vector< variant<paraVarType> > >&);
        ~mapController();

        int processInput(int c);

        const gmap& getCurrentMap();
        void setCurrentMap(std::string);

        int setPlayerPosition(Point a);
        Point getPlayerPosition();
        int movePlayer(Point a);
        const objPlayer& getPlayer() { return player; }

        bool isPlayerFacingObject();
        mapObject& getPlayerFacingObject();

        bool isPlayerOnObject();
        mapObject& getPlayerOnObject();


    protected:
    private:
        std::string currentMap;
        std::string defaultMap;
        std::map<std::string, gmap> map_list;
        unsigned int map_count;

        objPlayer player;

        Point getPlayerFacing();

        std::deque< std::vector< variant<paraVarType> > >& ctlCallStack;
};

#endif // MAPCONTROLLER_H
