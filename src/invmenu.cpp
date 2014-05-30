#include <curses.h>
#include <string>

#include "invmenu.h"
#include "utils.h"
#include "enum.h"
#include "utf8.h"

InvMenu::InvMenu(Engine* eng, std::map< std::string, variant<paraVarType> >& b) :
    Menu(eng, b)
{
    currentPos = 0;
    varMap["InvMenuCurPos"].set<unsigned int>(currentPos);   //ctor
}

InvMenu::~InvMenu()
{
    //dtor
}

/*
int InvMenu::processInput(int c){
    if(!processPending){
        switch (c) {
            case KEY_UP:
                currentPos = (currentPos==0)? 0 : currentPos - 1;
                break;
            case KEY_DOWN:
                currentPos = (currentPos == _limiter - 1 )? _limiter - 1 : currentPos + 1;
                currentPos = (_limiter > 0 )? currentPos : 0; // Empty Menu OverFlow safety Check
                break;
            case 'z':
                if(mode == 0){
                    if(_limiter > 0){
                        ctlCallStack.push_back(loadStack(svc::isItemUsable, currentPos));
                        processPending = 1;
                    }
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

        varMap["InvMenuCurPos"].set<unsigned int>(currentPos);

    }else if(processPending == 1){

        if(varMap["ret"].get<int>()){
            ctlCallStack.push_back(loadStack(svc::getItemType, currentPos));
            processPending = 2;
        }else{
            ctlCallStack.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar("This Item is not Comsumable"), UTF8_to_WChar("System")));
            processPending = 0;
        }

    }else if(processPending == 2){
        processPending = varMap["ret"].get<int>() + 3;
    }else if(processPending == 3){
        ctlCallStack.push_back(loadStack(svc::loadTeamMenu, 1));
        ctlCallStack.push_back(loadStack(svc::setStat, Stats::inTeamMenu));
        processPending = 4;
    }else if(processPending == 4){
        ctlCallStack.push_back(loadStack(svc::useItem, currentPos, varMap["TeamMenuCurPos"].get<unsigned int>()));
        processPending = 0;
    }

    return 0;
}
*/

void InvMenu::init(int val, int m){
    currentPos = 0;
    varMap["InvMenuCurPos"].set<unsigned int>(currentPos);
    _limiter = val;
    mode = m;
    processPending = 0;
}
