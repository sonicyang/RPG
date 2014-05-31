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

        virtual int hKeyUp() {return 0;};
        virtual int hKeyDown() {return 0;};
        virtual int hKeyLeft() {return 0;};
        virtual int hKeyRight() {return 0;};
        virtual int hKeyZ() {return 0;};
        virtual int hKeyX() {return 0;};
        virtual int hKeyQ() {return 0;};

        virtual int hDoEvent() {return 0;};

        virtual int hRender() {return 0;};
    protected:
        Engine* engine;
    private:
};

#endif // GENERICCONTORLLER_H
