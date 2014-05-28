#include <curses.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <string>
#include <algorithm>
#include "gmap.h"
#include "point.h"
#include "utils.h"
#include "json/reader.h"
#include "json/value.h"
#include "render.h"
#include "engine.h"
#include "variant.h"
#include "menu.h"
#include "itemexec.h"

Engine::Engine() :
    rdr(), ctlCall(),
    mapCtl("data/maps/maplist.lst", ctlCall),
    evtCtl("data/events/eventlist.lst", ctlCall, varMap),
    inv(),
    team("data/team/team_list.lst"),
    battle("data/monsters/monster_list.lst", inv, team, rdr),
    mainmenu(ctlCall, varMap),
    teammenu(ctlCall, varMap),
    invmenu(ctlCall, varMap),
    charmenu(ctlCall, varMap),
    skillmenu(ctlCall, varMap)
{

}

Engine::~Engine()
{
}

void Engine::getParseUserInput(){
    int c = getch();
    switch(stat){
        case onMap:
            mapCtl.processInput(c);
            break;
        case inEvent:
            evtCtl.processInput(c);
            break;
        case inMainMenu:
            mainmenu.processInput(c);
            break;
        case inTeamMenu:
            teammenu.processInput(c);
            break;
        case inInvMenu:
            invmenu.processInput(c);
            break;
        case inCharMenu:
            charmenu.processInput(c);
            break;
        case inSkillMenu:
            skillmenu.processInput(c);
            break;
    }
}

bool Engine::processCtlCall(){
    while(ctlCall.size() > 0){

		std::vector< variant<paraVarType> >currCall = ctlCall.front();

        int ret;

		int commd = currCall[0].get<svc>();
		switch(commd){
			case svc::loadEvent:
				evtCtl.pushEvent(currCall[1].get<std::string>());
				ret = 1;
				break;
			case svc::restoreStat:
				evtCtl.popEventStack();
				prom.discardMessage();
				this->restoreStat();
				ret = 1;
				break;
			case svc::setStat:
				this->setStat(currCall[1].get<Stats>());
				ret = 1;
				break;
			case svc::loadPrompt:
				prom.loadMessaage(currCall[1].get<wchar_t*>(), currCall[2].get<wchar_t*>());
				ret = 1;
				break;
			case svc::clearPrompt:
				prom.discardMessage();
				ret = 1;
				break;
			case svc::changeMap:
				mapCtl.setCurrentMap(currCall[1].get<std::string>());
				mapCtl.setPlayerPosition(Point(currCall[2].get<int>(), currCall[3].get<int>()));
				ret = 1;
				break;
            case svc::addItem:
                inv.addItem(currCall[1].get<std::string>(), currCall[2].get<int>());
                ret = 1;
                break;
            case svc::removeItem:
                ret = inv.removeItem(currCall[1].get<std::string>(), currCall[2].get<int>());
                break;
            case svc::incItem:
                inv.incItem(currCall[1].get<std::string>());
                ret = 1;
                break;
            case svc::decItem:
                ret = inv.decItem(currCall[1].get<std::string>());
                break;
            case svc::setMoney:
                inv.setMoney(currCall[1].get<int>());
                ret = 1;
                break;
            case svc::addMoney:
                inv.addMoney(currCall[1].get<int>());
                ret = 1;
                break;
            case svc::addCharToTeam:
                team.addCharToTeam(currCall[1].get<std::string>());
                ret = 1;
                break;
            case svc::removeCharFromTeam:
                team.removeCharFromTeam(currCall[1].get<std::string>());
                ret = 1;
                break;
            case svc::battle:
                //battle.battleStart(currCall[1].get< std::vector< std::string> >());
                break;
            case svc::loadMainMenu:
                mainmenu.init();
                ret = 1;
                break;
            case svc::loadTeamMenu:
                teammenu.init(team.getNameList().size(), currCall[1].get<int>());
                ret = 1;
                break;
            case svc::loadInvMenu:
                invmenu.init(inv.getNumOfItems(), currCall[1].get<int>());
                ret = 1;
                break;
            case svc::loadCharMenu:
                charmenu.init(currCall[1].get<int>());
                ret = 1;
                break;
            case svc::loadSkillMenu:
                skillmenu.init(team[team.getNameList()[varMap["TeamMenuCurPos"].get<unsigned int>()]].getSkillList().size(), currCall[1].get<int>());
                ret = 1;
                break;
            case svc::invEnableNull:
                inv.enableNull();
                ret = 1;
                break;
            case svc::invDisableNull:
                inv.disableNull();
                ret = 1;
                break;
            case svc::changeEquip:
                ItemExec::changeItem(inv, currCall[1].get<unsigned int>(), team, currCall[2].get<unsigned int>(), currCall[3].get<unsigned int>(), rdr);
                ret = 1;
                break;
            case svc::isItemUsable:
                ret = inv[inv.getNameList(currCall[1].get<unsigned int>())[0]].item.isUsable();
                break;
            case svc::getItemType:
                ret = inv[inv.getNameList(currCall[1].get<unsigned int>())[0]].item.getType();
                break;
            case svc::useItem:
                ItemExec::Exec(inv, currCall[1].get<unsigned int>(), team, currCall[2].get<unsigned int>(), rdr);
                ret = 1;
                break;
			case svc::endGame:
				return 0;
				break;
		}

		ctlCall.pop_front();

        varMap["ret"].set<int>(ret); //Save return value to Varible Map
    }
    return 1;
}

void Engine::updateScreen(){
    switch(stat){
        case Stats::onMap:
        case Stats::inEvent:
            rdr.render_map(mapCtl.getCurrentMap());
            rdr.render_Player(mapCtl.getPlayer());
            break;
        case Stats::inMainMenu:
            rdr.render_MainMenu(varMap["MainMenuCurPos"].get<unsigned int>(), mainmenu.getOptions());
            break;
        case Stats::inTeamMenu:
            rdr.render_TeamMenu(team, varMap["TeamMenuCurPos"].get<unsigned int>());
            break;
        case Stats::inInvMenu:
            rdr.render_InvMenu(inv, varMap["InvMenuCurPos"].get<unsigned int>());
            break;
        case Stats::inCharMenu:
            rdr.render_CharMenu(team[team.getNameList()[varMap["TeamMenuCurPos"].get<unsigned int>()]], varMap["CharMenuCurPos"].get<unsigned int>());
            break;
        case Stats::inSkillMenu:
            rdr.render_SkillMenu(team[team.getNameList()[varMap["TeamMenuCurPos"].get<unsigned int>()]], varMap["SkillMenuCurPos"].get<unsigned int>());
    }

    if(prom.hasMessage()){
        rdr.render_prompt(prom);
    }

    rdr.update();
    return;
}

/*
void Engine::menuRutin(){
    unsigned int cursorPos = 0;

    for(;;){
        rdr.render_MainMenu(cursorPos, mOption);

        //Wait User input
        int c = getch();
        switch (c) {
            case KEY_UP:
                cursorPos = (cursorPos==0)? mOption.size()-1 : cursorPos - 1;
                break;
            case KEY_DOWN:
                cursorPos = (cursorPos == mOption.size()-1)? 0 : cursorPos + 1;
                break;
            case 'z':
                switch(cursorPos){
                    case 0:
                        teamMenuRoutin();
                        break;
                    case 1:
                        invMenuRoutin();
                        break;
                    case 2:
                        prom.loadMessaage(L"Are You Sure?", L"System");
                        rdr.render_prompt(prom);
                        if(getch() == 'z'){
                            prom.loadMessaage(L"Bye", L"System");
                            rdr.render_prompt(prom);
                            getch();
                            ctlCall.push_back(loadStack(svc::endGame));
                            prom.discardMessage();
                            return;
                        }
                        break;
                }
                break;
            case 'x':
            case 'q':
                ctlCall.push_back(loadStack(svc::clearPrompt));
                return;
                break;
        }
    }
    return;
}

int Engine::invMenuRoutin(const int val){
    unsigned int currentPos = 0;

    std::vector<std::string> nameList = inv.getNameList(currentPos);

    for(;;){
        rdr.render_InvMenu(inv, currentPos);

        if(nameList.empty()){
            while(getch()!='x');
            return -1;
        }

        int c = getch();
        switch (c) {
            case KEY_UP:
                currentPos = (currentPos==0)? 0 : currentPos - 1;
                break;
            case KEY_DOWN:
                currentPos = (currentPos == nameList.size() - 1 )? nameList.size() - 1 : currentPos + 1;
                break;
            case 'z':
                switch(val){
                    case 0:
                        if(inv[nameList[0]].item.isUsable()){
                            switch(inv[nameList[0]].item.getType()){
                                case itemTypes::potion:
                                    int p = teamMenuRoutin(1);
                                    if( p == -1)
                                        break;
                                    team[team.getNameList()[p]].varHP(inv[nameList[0]].item.getHPVarient());
                                    team[team.getNameList()[p]].varMP(inv[nameList[0]].item.getMPVarient());
                                    break;
                                case itemTypes::allPotion:
                                    std::vector<std::string> memberList = team.getNameList();
                                    for(unsigned int i = 0; i < memberList.size(); i++){
                                        team[team.getNameList()[i]].varHP(inv[nameList[0]].item.getHPVarient());
                                        team[team.getNameList()[i]].varMP(inv[nameList[0]].item.getMPVarient());
                                    }
                                    break;
                            }

                            if(inv[nameList[0]].item.isComsumable())
                                inv.decItem(nameList[0]);
                        }else{
                            prom.loadMessaage(L"This Item is not Comsumable", L"System");
                            rdr.render_prompt(prom);
                            prom.discardMessage();
                            while(getch()!='z');
                        }

                        break;
                    case 1:
                        return currentPos;
                        break;
                }
                break;
            case 'x':
            case 'q':
                return -1;
                break;
        }

    }

    return -1;
}

int Engine::teamMenuRoutin(const int val){
    unsigned int currentPos = 0;

    std::vector<std::string> memberList = team.getNameList();

    for(;;){
        rdr.render_TeamMenu(team, currentPos);

        int c = getch();
        switch (c) {
            case KEY_UP:
                currentPos = (currentPos==0)? 0 : currentPos - 1;
                break;
            case KEY_DOWN:
                currentPos = (currentPos == memberList.size() - 1 )? memberList.size() - 1 : currentPos + 1;
                break;
            case 'z':
                switch(val){
                    case 0:
                        charMenuRoutin(0, memberList[currentPos]);
                        break;
                    case 1:
                        return currentPos;
                        break;
                }
                break;
            case 'x':
            case 'q':
                return -1;
                break;
        }

    }
    return -1;
}

int Engine::charMenuRoutin(const int val, std::string cname){
    unsigned int currentPos = 0;

    for(;;){
        rdr.render_CharMenu(team[cname], currentPos);

        int c = getch();
        switch (c) {
            case KEY_UP:
            case KEY_LEFT:
                currentPos = (currentPos==0)? 0 : currentPos - 1;
                break;
            case KEY_DOWN:
            case KEY_RIGHT:
                currentPos = (currentPos == 4 )? 4 : currentPos + 1;
                break;
            case 'z':
                switch(val){
                    case 0:{
                        inv.enableNull();

                        int p = invMenuRoutin(1);
                        if(p == -1)
                            break;

                        Item selectedItem = inv[inv.getNameList(p)[0]].item;

                        Item currItemName;
                        int ret;

                        switch(currentPos){
                            case 0:
                                currItemName = team[cname].getHead();
                                ret = team[cname].setHead(selectedItem);
                                break;
                            case 1:
                                currItemName = team[cname].getArmor();
                                ret = team[cname].setArmor(selectedItem);
                                break;
                            case 2:
                                currItemName = team[cname].getLegs();
                                ret = team[cname].setLegs(selectedItem);
                                break;
                            case 3:
                                currItemName = team[cname].getShoes();
                                ret = team[cname].setShoes(selectedItem);
                                break;
                            case 4:
                                currItemName = team[cname].getWeapon();
                                ret = team[cname].setWeapon(selectedItem);
                                break;
                        }

                        if(ret == -1){
                            prom.loadMessaage(L"You can't wear a shoe on your Head", L"System");
                            rdr.render_prompt(prom);
                            prom.discardMessage();
                            while(getch()!='z');
                        }else{
                            inv.decItem(inv.getNameList(p)[0]);
                            if(currItemName.getName() != "Empty")
                                inv.incItem(currItemName.getName());
                        }

                        inv.disableNull();
                        break;
                    }
                    case 1:
                        return currentPos;
                        break;
                }
                break;
            case 'x':
            case 'q':
                return -1;
                break;
        }

    }

    return -1;
}
*/

void Engine::setStat(int s){
    _stat.push_back(stat);
    stat = s;
    return;
}

void Engine::restoreStat(){
    if(_stat.size() > 0){
        stat = _stat.back();
        _stat.pop_back();
    }
    return;
}

