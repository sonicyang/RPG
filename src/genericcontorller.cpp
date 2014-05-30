#include "genericcontorller.h"

#include "engine.h"

genericContorller::genericContorller(Engine* eng) : engine(eng)
{

}

genericContorller::~genericContorller()
{
    //dtor
}

int genericContorller::hKeyUp(){
    return 0;
}

int genericContorller::hKeyDown(){
    return 0;
}

int genericContorller::hKeyLeft(){
    return 0;
}

int genericContorller::hKeyRight(){
    return 0;
}

int genericContorller::hKeyZ(){
    return 0;
}

int genericContorller::hKeyX(){
    return 0;
}

int genericContorller::hKeyQ(){
    return 0;
}

int genericContorller::hDoEvent(){
    return 0;
}

int genericContorller::hRender(){
    return 0;
}
