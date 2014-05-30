#ifndef CHARMENU_H
#define CHARMENU_H

#include <menu.h>

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

        void init(int m);
    protected:
    private:
        unsigned int currentPos;
        unsigned int mode;
        bool processPending = 0;
};

#endif // CHARMENU_H
