#include <curses.h>

#include "vender.h"

#include "utils.h"
#include "menu.h"

Vender::Vender(std::deque< std::vector< variant<paraVarType> > >& a, std::map< std::string, variant<paraVarType> >& b) :
    ctlCallStack(a),
    varMap(b)
{
    mOptions.push_back("Sell");
    mOptions.push_back("Buy");
    mOptions.push_back("Exit");
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
    varMap["VenderTopCurPos"].set<unsigned int>(topCurPos);
    venderInvCurPos = 0;
    return 0;
}

int Vender::processInput(int c){
    if(processStat == 0){
        switch (c) {
            case KEY_UP:
                topCurPos = (topCurPos==0)? 2 : topCurPos - 1;
                break;
            case KEY_DOWN:
                topCurPos = (topCurPos == 2)? 0 : topCurPos + 1;
                break;
            case 'z':
                switch(topCurPos){
                    case 0:
                        ctlCallStack.push_back(loadStack(svc::loadInvMenu, 1));
                        ctlCallStack.push_back(loadStack(svc::setStat, Stats::inInvMenu));
                        processStat = 1;
                        break;
                    case 1:
                        ctlCallStack.push_back(loadStack(svc::loadVenderInvMenu, 1));
                        ctlCallStack.push_back(loadStack(svc::setStat, Stats::inVendorInvMenu));
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
            ctlCallStack.push_back(loadStack(svc::setStat, Stats::inInvMenu));
        }
    }else if(processStat == 2){
        if(varMap["InvMenuCurPos"].get<unsigned int>() == 0xffffffff){
            processStat = 0;
        }else{
            unsigned int p = varMap["InvMenuCurPos"].get<unsigned int>();
            ctlCallStack.push_back(loadStack(svc::addMoney, (-1) * venderInv[venderInv.getNameList(p)[0]].item.getBuyPrice()));
            ctlCallStack.push_back(loadStack(svc::incItem, venderInv.getNameList(p)[0]));
            ctlCallStack.push_back(loadStack(svc::loadVenderInvMenu, 1));
            ctlCallStack.push_back(loadStack(svc::setStat, Stats::inVendorInvMenu));
        }
    }
    return 0;
}
