#ifndef OBJPLAYER_H
#define OBJPLAYER_H

#include <mapObject.h>
#include <string>


class objPlayer : public mapObject
{
    public:
        mapObject();
        mapObject(std::string, int, int, int, int, std::string, int);
        ~objPlayer();

        objPlayer(const objPlayer& other);
        objPlayer& operator=(const objPlayer& other);

        int getFaceing() { return facing; }
        void setFaceing(int);
    protected:
    private:
        std::string icon;
        int facing;
};

#endif // OBJPLAYER_H
