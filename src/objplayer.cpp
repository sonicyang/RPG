#include "objplayer.h"

objPlayer::objPlayer() : mapObject("NULL", 0, 0 , 0, 0, "@")
{
    //ctor
}

objPlayer::~objPlayer()
{
    //dtor
}

objPlayer::objPlayer(const objPlayer& other)
{
    //copy ctor
}

objPlayer& objPlayer::operator=(const objPlayer& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void objPlayer::setFaceing(int f){
    if(f < 0 || f > 3)
        return;
    facing = f;
    return;
}
