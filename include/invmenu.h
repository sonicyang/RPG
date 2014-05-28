#ifndef INVMENU_H
#define INVMENU_H

#include <menu.h>


class InvMenu : public Menu
{
    public:
        InvMenu(std::deque< std::vector< variant<paraVarType> > >&, std::map< std::string, variant<paraVarType> >&);
        virtual ~InvMenu();

        virtual int processInput(int);

        void init(int val, int m);
    protected:
    private:
        unsigned int currentPos;
        unsigned int _limiter;
        unsigned int mode;
        int processPending = 0;
};

#endif // INVMENU_H
