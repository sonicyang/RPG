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
    battle("data/monsters/monster_list.lst", ctlCall, varMap),
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
        case inBattle:
            battle.processInput(c);
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
            case svc::popEvent:
                evtCtl.popEventStack();
                ret = 1;
                break;
			case svc::restoreStat:
				prom.discardMessage();
				this->restoreStat();
				ret = 1;
				break;
			case svc::setStat:
			    prom.discardMessage();
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
                battle.loadBattle(team.getNameList().size(), currCall[1].get< std::vector< std::string> >());
                ctlCall.push_back(loadStack(svc::setStat, Stats::inBattle));
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
            case svc::isCharDead:
                ret = team[team.getNameList()[currCall[1].get<unsigned int>()]].isDead();
                break;
            case svc::isTeamWipeOut:
                ret = team.isWipeOut();
                break;
            case svc::queryAttack:
                ret = team[team.getNameList()[currCall[1].get<unsigned int>()]].getAttack();
                break;
            case svc::queryDefense:
                ret = team[team.getNameList()[currCall[1].get<unsigned int>()]].getDefense();
                break;
            case svc::varHP:
                team[team.getNameList()[currCall[1].get<unsigned int>()]].varHP(currCall[2].get<int>());
                ret = 1;
                break;
            case svc::varMP:
                team[team.getNameList()[currCall[1].get<unsigned int>()]].varMP(currCall[2].get<int>());
                ret = 1;
                break;
            case svc::varExp:
                team[team.getNameList()[currCall[1].get<unsigned int>()]].varExp(currCall[2].get<int>());
                ret = 1;
                break;
            case svc::moveVar:
                varMap[currCall[1].get<std::string>()].set<int>(varMap[currCall[2].get<std::string>()].get<int>());
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
            break;
        case Stats::inBattle:
            rdr.render_BattleScene(battle.getMonsters(), battle.getMonsterTag());
            rdr.render_BattleTeam(team, battle.getCurrentChara());
            rdr.render_BattleMenu(battle.getMenuPos());
            break;
    }

    if(prom.hasMessage()){
        rdr.render_prompt(prom);
    }

    rdr.update();
    return;
}

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

