#include <curses.h>

#include "teammenu.h"
#include "utils.h"
#include "enum.h"

TeamMenu::TeamMenu(std::deque< std::vector< variant<paraVarType> > >& a, std::map< std::string, variant<paraVarType> >& b) :
    Menu(a, b)
{
    //ctor
}

TeamMenu::~TeamMenu()
{
    //dtor
}

int TeamMenu::processInput(int c){

    switch (c) {
        case KEY_UP:
            currentPos = (currentPos == 0)? 0 : currentPos - 1;
            break;
        case KEY_DOWN:
            currentPos = (currentPos == _limiter - 1 )? _limiter - 1 : currentPos + 1;
            break;
        case 'z':
            return currentPos;
            break;
        case 'x':
        case 'q':
            ctlCallStack.push_back(loadStack(svc::restoreStat));
            break;
    }

    varMap["TeamMenuCurPos"].set<unsigned int>(currentPos);
    return 0;
}

void TeamMenu::init(int val){
    currentPos = 0;
    varMap["TeamMenuCurPos"].set<unsigned int>(currentPos);
    _limiter = val;
}
