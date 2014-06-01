#ifndef INVMENU_H
#define INVMENU_H

#include "menu.h"
#include "inventory.h"
#include "render.h"

class Engine;

class InvMenu : public Menu
{ 
    public:
        InvMenu(Engine*, std::map< std::string, variant<paraVarType> >&);
        virtual ~InvMenu();

        int hKeyUp();
        int hKeyDown();
        int hKeyZ();
        int hKeyX();
        int hKeyQ();

        int hRender(render&);

        void init(int m, inventory* i);
    protected:
    private:
        unsigned int currentPos;
        unsigned int _limiter;
        unsigned int mode;
        inventory* inv;
};

#endif // INVMENU_H
