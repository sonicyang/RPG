#ifndef INVMENU_H
#define INVMENU_H

#include <menu.h>

class Engine;

class InvMenu : public Menu
{
    public:
        InvMenu(Engine*, std::map< std::string, variant<paraVarType> >&);
        virtual ~InvMenu();

        void init(int val, int m);
    protected:
    private:
        unsigned int currentPos;
        unsigned int _limiter;
        unsigned int mode;
        int processPending = 0;
};

#endif // INVMENU_H
