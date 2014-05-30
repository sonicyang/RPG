#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H

#include "gmap.h"
#include "mapObject.h"
#include "objPLayer.h"
#include "variant.h"
#include "point.h"
#include "genericcontorller.h"

class Engine;
class genericContorller;

class mapController : public genericContorller
{
    public:
        mapController(std::string maplist, Engine* eng);
        ~mapController();

        int hKeyUp();
        int hKeyDown();
        int hKeyLeft();
        int hKeyRight();
        int hKeyZ();
        int hKeyX();
        int hKeyQ();

        int hDoEvent();

        int hRender();

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

        //std::deque< std::vector< variant<paraVarType> > >& ctlCallStack;
};

#endif // MAPCONTROLLER_H
