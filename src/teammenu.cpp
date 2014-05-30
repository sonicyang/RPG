#include <curses.h>

#include "teammenu.h"
#include "utils.h"
#include "enum.h"

TeamMenu::TeamMenu(Engine* eng, std::map< std::string, variant<paraVarType> >& b) :
    Menu(eng, b)
{
    currentPos = 0;
    varMap["TeamMenuCurPos"].set<unsigned int>(currentPos);
}

TeamMenu::~TeamMenu()
{
    //dtor
}

/*
int TeamMenu::processInput(int c){

    switch (c) {
        case KEY_UP:
            currentPos = (currentPos == 0)? 0 : currentPos - 1;
            break;
        case KEY_DOWN:
            currentPos = (currentPos == _limiter - 1 )? _limiter - 1 : currentPos + 1;
            break;
        case 'z':
            if(mode == 0){
                ctlCallStack.push_back(loadStack(svc::loadCharMenu, 0));
                ctlCallStack.push_back(loadStack(svc::setStat, Stats::inCharMenu));
            }else{
                ctlCallStack.push_back(loadStack(svc::restoreStat));
            }
            break;
        case 'x':
        case 'q':
            currentPos = 0xffffffff;
            ctlCallStack.push_back(loadStack(svc::restoreStat));
            break;
    }

    varMap["TeamMenuCurPos"].set<unsigned int>(currentPos);
    return 0;
}
*/

void TeamMenu::init(int val, int m){
    currentPos = 0;
    varMap["TeamMenuCurPos"].set<unsigned int>(currentPos);
    _limiter = val;
    mode = m;
}
