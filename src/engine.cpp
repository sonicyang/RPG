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
#include "utf8.h"

Engine::Engine() :
    rdr(), ctlCall(),
    mapCtl("data/maps/maplist.lst", this),
    evtCtl("data/events/eventlist.lst", this, varMap),
    inv(),
    team("data/team/team_list.lst"),
    battle("data/monsters/monster_list.lst", ctlCall, varMap),
    mainmenu(ctlCall, varMap),
    teammenu(ctlCall, varMap),
    invmenu(ctlCall, varMap),
    charmenu(ctlCall, varMap),
    skillmenu(ctlCall, varMap),
    vendor(ctlCall, varMap)
{

}

Engine::~Engine()
{
}

void Engine::getParseUserInput(){
    int c = getch();
    switch(stat){
        case onMap:
            //mapCtl.processInput(c);
            break;
        case inEvent:
            //evtCtl.processInput(c);
            break;
        case inMainMenu:
            mainmenu.processInput(c);
            break;
        case inTeamMenu:
            teammenu.processInput(c);
            break;
        case inInvMenu:
        case inVendorInvMenu:
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
        case inPrompt:
            if(c == 'z'){
                prom.discardMessage();
                this->restoreStat();
            }
            break;
        case inVender:
            vendor.processInput(c);
            break;
    }
}

void Engine::parseUserInput(){
    int c = getch();
    switch(c){
        case KEY_UP:
            controllerStack.back()->hKeyUp();
            break;
        case KEY_DOWN:
            controllerStack.back()->hKeyDown();
            break;
        case KEY_LEFT:
            controllerStack.back()->hKeyLeft();
            break;
        case KEY_RIGHT:
            controllerStack.back()->hKeyRight();
            break;
        case 'z':
            controllerStack.back()->hKeyZ();
            break;
        case 'x':
            controllerStack.back()->hKeyX();
            break;
        case 'q':
            controllerStack.back()->hKeyQ();
            break;

    }

}

void Engine::excute(){
    controllerStack.push_back(&mapCtl);

    for(;!stop;){
        parseUserInput();
        controllerStack.back()->hDoEvent();
        controllerStack.back()->hRender();
    }


}

variant<paraVarType> Engine::engineCall(std::vector< variant<paraVarType> > params){
    char tmp[100];

    variant<paraVarType> ret;
    ret.set<int>(1);

    int commd = params[0].get<svc>();
    switch(commd){
        case svc::loadEvent:
            evtCtl.pushEvent(params[1].get<std::string>());
            break;
        case svc::popEvent:
            evtCtl.popEventStack();
            break;
        case svc::restoreStat:
            prom.discardMessage();
            this->restoreStat();
            break;
        case svc::setStat:
            this->setStat(params[1].get<Stats>());
            break;
        case svc::loadPrompt:
            prom.loadMessaage(params[1].get<wchar_t*>(), params[2].get<wchar_t*>());
            this->setStat(Stats::inPrompt);
            break;
        case svc::clearPrompt:
            prom.discardMessage();
            break;
        case svc::changeMap:
            mapCtl.setCurrentMap(params[1].get<std::string>());
            mapCtl.setPlayerPosition(Point(params[2].get<int>(), params[3].get<int>()));
            break;
        case svc::addItem:
            inv.addItem(params[1].get<std::string>(), params[2].get<int>());
            sprintf(tmp, "You get %d %s", params[2].get<int>(), params[1].get<std::string>().c_str());
            ctlCall.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar(tmp), UTF8_to_WChar("System")));
            break;
        case svc::removeItem:
            ret.set<int>(inv.removeItem(params[1].get<std::string>(), params[2].get<int>()));
            sprintf(tmp, "You lost %d %s", params[2].get<int>(), params[1].get<std::string>().c_str());
            ctlCall.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar(tmp), UTF8_to_WChar("System")));
            break;
        case svc::incItem:
            inv.incItem(params[1].get<std::string>());
            sprintf(tmp, "You get a %s", params[1].get<std::string>().c_str());
            ctlCall.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar(tmp), UTF8_to_WChar("System")));
            break;
        case svc::decItem:
            ret.set<int>(inv.decItem(params[1].get<std::string>()));
            sprintf(tmp, "You lost a %s", params[1].get<std::string>().c_str());
            ctlCall.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar(tmp), UTF8_to_WChar("System")));
            break;
        case svc::setMoney:
            inv.setMoney(params[1].get<int>());
            sprintf(tmp, "You Currently Have $%d", inv.getMoney());
            break;
        case svc::addMoney:
            inv.addMoney(params[1].get<int>());

            if(params[1].get<int>() > 0)
                sprintf(tmp, "You gained $%d", params[1].get<int>());
            else if(params[1].get<int>() < 0)
                sprintf(tmp, "You lost $%d", (-1)* params[1].get<int>());
            if(params[1].get<int>() != 0)
                ctlCall.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar(tmp), UTF8_to_WChar("System")));
            break;
        case svc::addCharToTeam:
            team.addCharToTeam(params[1].get<std::string>());
            sprintf(tmp, "%s joined the Team", params[1].get<std::string>().c_str());
            ctlCall.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar(tmp), UTF8_to_WChar("System")));
            break;
        case svc::removeCharFromTeam:
            team.removeCharFromTeam(params[1].get<std::string>());
            sprintf(tmp, "%s leaved the Team", params[1].get<std::string>().c_str());
            ctlCall.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar(tmp), UTF8_to_WChar("System")));
            break;
        case svc::battle:
            battle.loadBattle(team.getNameList().size(), params[1].get< std::vector< std::string> >());
            ctlCall.push_back(loadStack(svc::setStat, Stats::inBattle));
            break;
        case svc::loadMainMenu:
            mainmenu.init();
            break;
        case svc::loadTeamMenu:
            teammenu.init(team.getNameList().size(), params[1].get<int>());
            break;
        case svc::loadInvMenu:
            invmenu.init(inv.getNumOfItems(), params[1].get<int>());
            break;
        case svc::loadCharMenu:
            charmenu.init(params[1].get<int>());
            break;
        case svc::loadSkillMenu:
            skillmenu.init(team[team.getNameList()[varMap["TeamMenuCurPos"].get<unsigned int>()]].getSkillList().size(), params[1].get<int>());
            break;
        case svc::invEnableNull:
            inv.enableNull();
            break;
        case svc::invDisableNull:
            inv.disableNull();
            break;
        case svc::changeEquip:
            ItemExec::changeItem(inv, params[1].get<unsigned int>(), team, params[2].get<unsigned int>(), params[3].get<unsigned int>(), rdr);
            break;
        case svc::isItemUsable:
            ret.set<int>(inv[inv.getNameList(params[1].get<unsigned int>())[0]].item.isUsable());
            break;
        case svc::getItemType:
            ret.set<int>(inv[inv.getNameList(params[1].get<unsigned int>())[0]].item.getType());
            break;
        case svc::useItem:
            ItemExec::Exec(inv, params[1].get<unsigned int>(), team, params[2].get<unsigned int>(), rdr);
            sprintf(tmp, "Used %s", inv[inv.getNameList(params[1].get<unsigned int>())[0]].item.getName().c_str());
            ctlCall.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar(tmp), UTF8_to_WChar("System")));
            break;
        case svc::isCharDead:
            ret.set<int>(team[team.getNameList()[params[1].get<unsigned int>()]].isDead());
            break;
        case svc::isTeamWipeOut:
            ret.set<int>(team.isWipeOut());
            break;
        case svc::queryAttack:
            ret.set<int>(team[team.getNameList()[params[1].get<unsigned int>()]].getAttack());
            break;
        case svc::queryDefense:
            ret.set<int>(team[team.getNameList()[params[1].get<unsigned int>()]].getDefense());
            break;
        case svc::varHP:
            team[team.getNameList()[params[1].get<unsigned int>()]].varHP(params[2].get<int>());
            if(params[2].get<int>() > 0)
                sprintf(tmp, "%s HP recovered by %d points", team.getNameList()[params[1].get<unsigned int>()].c_str(), params[2].get<int>());
            else if(params[2].get<int>() < 0)
                sprintf(tmp, "%s received damage by %d points", team.getNameList()[params[1].get<unsigned int>()].c_str(), (-1)* params[2].get<int>());
            if(params[2].get<int>() != 0)
                ctlCall.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar(tmp), UTF8_to_WChar("System")));
            break;
        case svc::varMP:
            team[team.getNameList()[params[1].get<unsigned int>()]].varMP(params[2].get<int>());
            if(params[2].get<int>() > 0)
                sprintf(tmp, "%s MP increased by %d points", team.getNameList()[params[1].get<unsigned int>()].c_str(), params[2].get<int>());
            else if(params[2].get<int>() < 0)
                sprintf(tmp, "%s MP decreased by %d points", team.getNameList()[params[1].get<unsigned int>()].c_str(), (-1)* params[2].get<int>());
            if(params[2].get<int>() != 0)
                ctlCall.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar(tmp), UTF8_to_WChar("System")));
            break;
        case svc::varExp:
            team[team.getNameList()[params[1].get<unsigned int>()]].varExp(params[2].get<int>());
            if(params[2].get<int>() > 0)
                sprintf(tmp, "%s experience increased by %d points", team.getNameList()[params[1].get<unsigned int>()].c_str(), params[2].get<int>());
            else if(params[2].get<int>() < 0)
                sprintf(tmp, "%s experience decreased by %d points", team.getNameList()[params[1].get<unsigned int>()].c_str(), (-1)* params[2].get<int>());
            if(params[2].get<int>() != 0)
                ctlCall.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar(tmp), UTF8_to_WChar("System")));
            break;
        case svc::moveVar:
            varMap[params[1].get<std::string>()].set<int>(varMap[params[2].get<std::string>()].get<int>());
            break;
        case svc::qureySkillMonsterMenuRequired:
            ret.set<int>(team[team.getNameList()[params[1].get<unsigned int>()]].getSkillList()[params[2].get<unsigned int>()].geteTarget());
            break;
        case svc::qureySkillTeamMenuRequired:
            ret.set<int>(team[team.getNameList()[params[1].get<unsigned int>()]].getSkillList()[params[2].get<unsigned int>()].getfTarget());
            break;
        case svc::useSkill:
            ret.set<int>(ItemExec::skillExec(team, params[1].get<unsigned int>(), params[2].get<unsigned int>(), battle.getMonsters(), params[3].get<unsigned int>(), params[4].get<unsigned int>(), rdr));
            break;
        case svc::setupVender:
            vendor.setUp(params[1].get<std::vector<std::string> >());
            break;
        case svc::loadVenderInvMenu:
            invmenu.init(vendor.getVenderInv().getNumOfItems(), params[1].get<int>());
            vendor.getVenderInv().setMoney(inv.getMoney());
            break;
        case svc::sellItem:
            ctlCall.push_back(loadStack(svc::addMoney, inv[inv.getNameList(params[1].get<unsigned int>())[0]].item.getSellPrice()));
            ctlCall.push_back(loadStack(svc::decItem, inv.getNameList(params[1].get<unsigned int>())[0]));
            break;
        case svc::gameOver:
            stop = 1;
            ret.set<int>(-1);
            break;
        case svc::endGame:
            stop = 1;
            ret.set<int>(0);
            break;
    }
    return ret;
}

void Engine::updateScreen(){
    switch(stat){
        case Stats::onMap:
        case Stats::inEvent:
            //rdr.render_map(mapCtl.getCurrentMap());
            //rdr.render_Player(mapCtl.getPlayer());
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
        case Stats::inVendorInvMenu:
            rdr.render_InvMenu(vendor.getVenderInv(), varMap["InvMenuCurPos"].get<unsigned int>());
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
        case Stats::inVender:
            switch(vendor.getProcessStat()){
                case 0:
                    rdr.render_VenderMenu(varMap["VenderTopCurPos"].get<unsigned int>(), vendor.getOptions());
                    break;
                case 1:
                    break;
                case 2:
                    break;
            }
            break;
    }

    if(prom.hasMessage()){
        rdr.render_prompt(prom);
    }

    rdr.update();
    return;
}

void Engine::setStat(int s){
    switch(s){
        case onMap:
            controllerStack.push_back(&mapCtl);
            break;
        case inEvent:
            controllerStack.push_back(&evtCtl);
            break;
        case inMainMenu:
           //mainmenu.processInput(c);
            break;
        case inTeamMenu:
            //teammenu.processInput(c);
            break;
        case inInvMenu:
        case inVendorInvMenu:
            //invmenu.processInput(c);
            break;
        case inCharMenu:
            //charmenu.processInput(c);
            break;
        case inSkillMenu:
            //skillmenu.processInput(c);
            break;
        case inBattle:
            //battle.processInput(c);
            break;
        case inPrompt:
            //if(c == 'z'){
            //    prom.discardMessage();
             //   this->restoreStat();
            //}
            break;
        case inVender:
            //vendor.processInput(c);
            break;
    }
    return;
}

void Engine::restoreStat(){
    if(controllerStack.size() > 0){
        controllerStack.pop_back();
    }
    return;
}

