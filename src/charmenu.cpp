#include <curses.h>

#include "charmenu.h"
#include "utils.h"
#include "enum.h"

CharMenu::CharMenu(Engine* eng, std::map< std::string, variant<paraVarType> >& b) :
    Menu(eng, b)
{
    currentPos = 0;
    varMap["CharMenuCurPos"].set<unsigned int>(currentPos);
}

CharMenu::~CharMenu()
{
    //dtor
}

int MainMenu::hKeyUp(){
    currentPos = (currentPos==0)? 5 : currentPos - 1;
    return 0;
}

int MainMenu::hKeyDown(){
    currentPos = (currentPos == 5)? 0 : currentPos + 1;
    return 0;
}

int MainMenu::hKeyZ(){
    varMap["CharMenuCurPos"].set<unsigned int>(currentPos);
    if(mode == 0){
        if(currentPos < 5){
            engine->engineCall(loadStack(svc::invEnableNull));
            engine->engineCall(loadStack(svc::loadInvMenu, 1));
            engine->engineCall(loadStack(svc::setStat, Stats::inInvMenu));
            processPending = 1;
        }else{
            engine->engineCall(loadStack(svc::loadSkillMenu, 1));
            engine->engineCall(loadStack(svc::setStat, Stats::inSkillMenu));
        }
    }else{
        engine->engineCall(loadStack(svc::restoreStat));
    }
    return 0;
}

int MainMenu::hKeyX(){
    varMap["CharMenuCurPos"].set<unsigned int>(0xffffffff);
    engine->engineCall(loadStack(svc::restoreStat));
    return 0;
}

int MainMenu::hKeyQ(){
    varMap["CharMenuCurPos"].set<unsigned int>(0xffffffff);
    engine->engineCall(loadStack(svc::restoreStat));
    return 0;
}

int CharMenu::hDoEvent(){
    if(processPending){
        engine->engineCall(loadStack(svc::changeEquip, varMap["InvMenuCurPos"].get<unsigned int>(), varMap["TeamMenuCurPos"].get<unsigned int>(), currentPos));
        engine->engineCall(loadStack(svc::invDisableNull));
        processPending = 0;
    }
    return 0;
}

int MainMenu::hRender(){
    render::render_MainMenu(currentPos, mOption);
    return 0;
}

void CharMenu::init(int m){
    currentPos = 0;
    varMap["CharMenuCurPos"].set<unsigned int>(currentPos);
    mode = m;
    processPending = 0;
}
