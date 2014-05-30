#ifndef TEAMMENU_H
#define TEAMMENU_H

#include <menu.h>

class Engine;

class TeamMenu : public Menu
{
    public:
        TeamMenu(Engine*, std::map< std::string, variant<paraVarType> >&);
        virtual ~TeamMenu();



        void init(int val, int m);
    protected:
    private:
        unsigned int currentPos;
        unsigned int _limiter;
        unsigned int mode;
};

#endif // TEAMMENU_H
