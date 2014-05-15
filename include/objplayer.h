#ifndef OBJPLAYER_H
#define OBJPLAYER_H

#include <string>
#include "mapObject.h"

class objPlayer : public mapObject
{
    public:
        objPlayer();
        objPlayer(std::string n, int i, int t, int x, int y, std::string ic, int f);
        ~objPlayer();

        objPlayer(const objPlayer& other);
        objPlayer& operator=(const objPlayer& other);

        virtual char Geticon() const { return icon_list[facing]; };

        int getFacing() { return facing; }
        void setFacing(int);
    protected:
    private:
        std::string icon_list;
        int facing;
};

#endif // OBJPLAYER_H
