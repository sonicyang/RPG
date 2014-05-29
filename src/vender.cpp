#include <curses.h>

#include "vender.h"

#include "utils.h"
#include "menu.h"

Vender::Vender(std::deque< std::vector< variant<paraVarType> > >& a, std::map< std::string, variant<paraVarType> >& b) :
    ctlCallStack(a),
    varMap(b)
{
    //ctor
}

Vender::~Vender()
{
    //dtor
}

int Vender::setUp(std::vector<std::string> nameList){
    venderInv.clearInv();
    for(unsigned int i = 0; i < nameList.size(); i++){
        venderInv.incItem(nameList[i]);
    }
    processStat = 0;
    topCurPos = 0;
    venderInvCurPos = 0;
    return 0;
}

int Vender::processInput(int c){
    if(processStat == 0){
        switch (c) {
            case KEY_LEFT:
                topCurPos = (topCurPos==0)? 2 : topCurPos - 1;
                break;
            case KEY_RIGHT:
                topCurPos = (topCurPos == 2)? 0 : topCurPos + 1;
                break;
            case 'z':
                switch(topCurPos){
                    case 0:
                        ctlCallStack.push_back(loadStack(svc::loadInvMenu, 1));
                        processStat = 1;
                        break;
                    case 1:
                        ctlCallStack.push_back(loadStack(svc::loadVenderInvMenu, 1));
                        processStat = 2;
                        break;
                    case 2:
                        ctlCallStack.push_back(loadStack(svc::restoreStat));
                        break;
                }
                break;
            case 'x':
                ctlCallStack.push_back(loadStack(svc::restoreStat));
                break;
        }

        varMap["VenderTopCurPos"].set<unsigned int>(topCurPos);
    }else if(processStat == 1){
        if(varMap["InvMenuCurPos"].get<unsigned int>() == 0xffffffff){
            processStat = 0;
        }else{
            ctlCallStack.push_back(loadStack(svc::sellItem, varMap["InvMenuCurPos"].get<unsigned int>()));
            ctlCallStack.push_back(loadStack(svc::loadInvMenu, 1));
        }
    }else if(processStat == 2){
        if(varMap["InvMenuCurPos"].get<unsigned int>() == 0xffffffff){
            processStat = 0;
        }else{
            //ctlCallStack.push_back(loadStack(svc::buyItem, varMap["InvMenuCurPos"].get<unsigned int>()));
            ctlCallStack.push_back(loadStack(svc::loadVenderInvMenu, 1));
        }
    }
    return 0;
}
