#ifndef CHARMENU_H
#define CHARMENU_H

#include "menu.h"
#include "character.h"

class Engine;

class CharMenu : public Menu
{
    public:
        CharMenu(Engine*, std::map< std::string, variant<paraVarType> >&);
        virtual ~CharMenu();

        int hKeyUp();
        int hKeyDown();
        int hKeyZ();
        int hKeyX();
        int hKeyQ();

        int hDoEvent();

        int hRender();

        void init(int m, Character*);
    protected:
    private:
        unsigned int currentPos;
        unsigned int mode;
        Character* currChara;
};

#endif // CHARMENU_H
