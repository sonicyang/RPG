#include <curses.h>

#include "invmenu.h"
#include "utils.h"
#include "enum.h"

InvMenu::InvMenu(std::deque< std::vector< variant<paraVarType> > >& a, std::map< std::string, variant<paraVarType> >& b) :
    Menu(a, b)
{
    //ctor
}

InvMenu::~InvMenu()
{
    //dtor
}

int InvMenu::processInput(int c){

    switch (c) {
        case KEY_UP:
            currentPos = (currentPos==0)? 0 : currentPos - 1;
            break;
        case KEY_DOWN:
            currentPos = (currentPos == _limiter - 1 )? _limiter - 1 : currentPos + 1;
            currentPos = (_limiter > 0 )? currentPos : 0; // Empty Menu OverFlow safety Check
            break;
        case 'z':
            if(_limiter > 0){

            }
            break;
        case 'x':
        case 'q':
            ctlCallStack.push_back(loadStack(svc::restoreStat));
            break;
    }

    varMap["InvMenuCurPos"].set<unsigned int>(currentPos);
    return 0;
}

void InvMenu::init(int val){
    currentPos = 0;
    varMap["InvMenuCurPos"].set<unsigned int>(currentPos);
    _limiter = val;
}
