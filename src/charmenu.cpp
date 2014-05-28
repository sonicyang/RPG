#include <curses.h>

#include "charmenu.h"
#include "utils.h"
#include "enum.h"

CharMenu::CharMenu(std::deque< std::vector< variant<paraVarType> > >& a, std::map< std::string, variant<paraVarType> >& b) :
    Menu(a, b)
{
    //ctor
}

CharMenu::~CharMenu()
{
    //dtor
}

int CharMenu::processInput(int c){

    switch (c) {
        case KEY_UP:
            currentPos = (currentPos==0)? 0 : currentPos - 1;
            break;
        case KEY_DOWN:
            currentPos = (currentPos == 5 )? 5 : currentPos + 1;
            break;
        case 'z':

            break;
        case 'x':
        case 'q':
            ctlCallStack.push_back(loadStack(svc::restoreStat));
            break;
    }

    varMap["CharMenuCurPos"].set<unsigned int>(currentPos);
    return 0;
}

void CharMenu::init(){
    currentPos = 0;
    varMap["CharMenuCurPos"].set<unsigned int>(currentPos);
}
