#ifndef MENU_H
#define MENU_H

#include <map>
#include <vector>
#include <deque>
#include "utils.h"

class Menu
{
    public:

        Menu(std::deque< std::vector< variant<paraVarType> > >&, std::map< std::string, variant<paraVarType> >&);
        ~Menu();

        virtual int processInput(int) = 0;

    protected:
        std::deque< std::vector< variant<paraVarType> > >& ctlCallStack;
        std::map< std::string, variant<paraVarType> >& varMap;
    private:


};

#endif // MENU_H
