#ifndef GENERICCONTORLLER_H
#define GENERICCONTORLLER_H

#include "variant.h"
#include "utils.h"

class Engine;

class genericContorller
{
    public:
        genericContorller(Engine *);
        virtual ~genericContorller();

        virtual int hKeyUp();
        virtual int hKeyDown();
        virtual int hKeyLeft();
        virtual int hKeyRight();
        virtual int hKeyZ();
        virtual int hKeyX();
        virtual int hKeyQ();

        virtual int hDoEvent();

        virtual int hRender();
    protected:
        Engine* engine;
    private:
};

#endif // GENERICCONTORLLER_H
