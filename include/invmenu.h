#ifndef INVMENU_H
#define INVMENU_H

#include <menu.h>


class InvMenu : public Menu
{
    public:
        InvMenu(std::deque< std::vector< variant<paraVarType> > >&, std::map< std::string, variant<paraVarType> >&);
        virtual ~InvMenu();

        virtual int processInput(int);

        void init(int val);
    protected:
    private:
        unsigned int currentPos;
        unsigned int _limiter;
};

#endif // INVMENU_H
