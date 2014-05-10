#ifndef OBJPLAYER_H
#define OBJPLAYER_H

#include <mapObject.h>
#include <string>


class objPlayer : public mapObject
{
    public:
        objPlayer();
        objPlayer(std::string n, int i, int t, int x, int y, std::string ic, int f);
        ~objPlayer();

        objPlayer(const objPlayer& other);
        objPlayer& operator=(const objPlayer& other);

        virtual char Geticon() { return icon_list[facing]; };

        int getFaceing() { return facing; }
        void setFaceing(int);
    protected:
    private:
        std::string icon_list;
        int facing;
};

#endif // OBJPLAYER_H
