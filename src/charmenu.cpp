#include <curses.h>

#include "charmenu.h"
#include "utils.h"
#include "enum.h"

CharMenu::CharMenu(std::deque< std::vector< variant<paraVarType> > >& a, std::map< std::string, variant<paraVarType> >& b) :
    Menu(a, b)
{
    currentPos = 0;
    varMap["CharMenuCurPos"].set<unsigned int>(currentPos);
}

CharMenu::~CharMenu()
{
    //dtor
}

int CharMenu::processInput(int c){
    if(!processPending){
        switch (c) {
            case KEY_UP:
                currentPos = (currentPos==0)? 0 : currentPos - 1;
                break;
            case KEY_DOWN:
                currentPos = (currentPos == 5 )? 5 : currentPos + 1;
                break;
            case 'z':
                if(mode == 0){
                    if(currentPos < 5){
                        ctlCallStack.push_back(loadStack(svc::invEnableNull));
                        ctlCallStack.push_back(loadStack(svc::loadInvMenu, 1));
                        ctlCallStack.push_back(loadStack(svc::setStat, Stats::inInvMenu));
                        processPending = 1;
                    }else{
                        ctlCallStack.push_back(loadStack(svc::loadSkillMenu, 1));
                        ctlCallStack.push_back(loadStack(svc::setStat, Stats::inSkillMenu));
                    }
                }else{
                    ctlCallStack.push_back(loadStack(svc::restoreStat));
                }
                break;
            case 'x':
            case 'q':
                ctlCallStack.push_back(loadStack(svc::restoreStat));
                break;
        }

        varMap["CharMenuCurPos"].set<unsigned int>(currentPos);
    }else{
        ctlCallStack.push_back(loadStack(svc::changeEquip, varMap["InvMenuCurPos"].get<unsigned int>(), varMap["TeamMenuCurPos"].get<unsigned int>(), currentPos));
        ctlCallStack.push_back(loadStack(svc::invDisableNull));
        processPending = 0;
    }

    return 0;
}

void CharMenu::init(int m){
    currentPos = 0;
    varMap["CharMenuCurPos"].set<unsigned int>(currentPos);
    mode = m;
    processPending = 0;
}
