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

Engine::Engine() :
    rdr(), ctlCall(),
    mapCtl("data/maps/maplist.lst", ctlCall),
    evtCtl("data/events/eventlist.lst", ctlCall, varMap),
    inv(),
    team("data/team/team_list.lst"),
    mOption(3)
{
        mOption[0] = "Team";
        mOption[1] = "Inventory";
        mOption[2] = "Exit";
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
        case menu:
            nodelay(stdscr, false); //Nasty Hack
            menuRutin();
            nodelay(stdscr, true);
            this->restoreStat();
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
                break;
            case svc::removeCharFromTeam:
                team.removeCharFromTeam(currCall[1].get<std::string>());
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
        case Stats::menu:

            break;
    }

    if(prom.hasMessage()){
        rdr.render_prompt(prom);
    }

    rdr.update();
    return;
}

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

void Engine::invMenuRoutin(){
    unsigned int currentPos = 0;

    for(;;){
        rdr.render_InvMenu(inv, currentPos);

        std::vector<std::string> nameList = inv.getNameList(currentPos);

        if(nameList.empty()){
            while(getch()!='x');
            return;
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
                //inv[nameList[0]].item
                break;
            case 'x':
            case 'q':
                return;
                break;
        }

    }

    return;
}

void Engine::teamMenuRoutin(){
        clear();
        mvaddstr(0, 0, "================================================================================");
        for(int i = 1; i < 24; i++)mvaddch(i, 0, '|'),mvaddch(i, 79, '|');
        mvaddstr(24, 0, "===============================================================================");
        mvaddstr(2, 0, "================================================================================");
        mvaddstr(1, 38, "TEAM");

        std::vector<std::string> memberList = team.getNameList();



        for (unsigned int i = 0; i < memberList.size(); i++){
            mvaddstr(3 + i * 5, 1, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            mvaddstr(3 + i * 5 + 5, 1, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

            char tmp[10];

            //Print Informations
            mvaddstr(3 + i * 5 + 1, 2, "Name:");
            mvaddstr(3 + i * 5 + 1, 8, team[memberList[i]].getName().c_str());

            mvaddstr(3 + i * 5 + 1, 25, "Level:");
            sprintf(tmp, "%d", team[memberList[i]].getLevel());
            mvaddstr(3 + i * 5 + 1, 32, tmp);

            mvaddstr(3 + i * 5 + 1, 40, "Role:");
            mvaddstr(3 + i * 5 + 1, 46, team[memberList[i]].getRole().getName().c_str());

            mvaddstr(3 + i * 5 + 2, 2, "HP:");
            sprintf(tmp, "%d", team[memberList[i]].getHP());
            mvaddstr(3 + i * 5 + 2, 6, tmp);
            sprintf(tmp, "/%d", team[memberList[i]].getRole().getMaxHP());
            addstr(tmp);

            mvaddstr(3 + i * 5 + 3, 2, "MP:");
            sprintf(tmp, "%d", team[memberList[i]].getHP());
            mvaddstr(3 + i * 5 + 3, 6, tmp);
            sprintf(tmp, "/%d", team[memberList[i]].getRole().getMaxHP());
            addstr(tmp);

            mvaddstr(3 + i * 5 + 2, 20, "EXP:");
            sprintf(tmp, "%d", team[memberList[i]].getExp());
            mvaddstr(3 + i * 5 + 2, 25, tmp);
            sprintf(tmp, "/%d", team[memberList[i]].getRole().getLevelUpExp());
            addstr(tmp);
        }

    while(getch()!='x');
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

