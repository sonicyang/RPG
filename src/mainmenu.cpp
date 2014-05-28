#include <curses.h>

#include "mainmenu.h"
#include "utils.h"
#include "enum.h"

MainMenu::MainMenu(std::deque< std::vector< variant<paraVarType> > >& a, std::map< std::string, variant<paraVarType> >& b) :
    Menu(a, b)
{
    mOption.push_back("Team");
    mOption.push_back("Inventory");
    mOption.push_back("Exit");

}

MainMenu::~MainMenu()
{

}

int MainMenu::processInput(int c){
    //Wait User input
    switch (c) {
        case KEY_UP:
            currentPos = (currentPos==0)? mOption.size() - 1 : currentPos - 1;
            break;
        case KEY_DOWN:
            currentPos = (currentPos == mOption.size() - 1)? 0 : currentPos + 1;
            break;
        case 'z':
            switch(currentPos){
            case 0:
                ctlCallStack.push_back(loadStack(svc::loadTeamMenu));
                ctlCallStack.push_back(loadStack(svc::setStat, Stats::inTeamMenu));
                break;
            case 1:
                ctlCallStack.push_back(loadStack(svc::loadInvMenu));
                ctlCallStack.push_back(loadStack(svc::setStat, Stats::inInvMenu));
                break;
            case 2:
                ctlCallStack.push_back(loadStack(svc::endGame));
                break;
            }


            break;
        case 'x':
        case 'q':
            ctlCallStack.push_back(loadStack(svc::restoreStat));
            break;
    }

    varMap["MainMenuCurPos"].set<unsigned int>(currentPos);
    return 0;
}

void MainMenu::init(void){
    currentPos = 0;
    varMap["MainMenuCurPos"].set<unsigned int>(currentPos);
}

