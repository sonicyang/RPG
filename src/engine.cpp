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

Engine::Engine() : rdr(), ctlCall(), mapCtl("data/maps/maplist.lst", ctlCall), evtCtl("data/events/eventlist.lst", ctlCall), inv()
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
        case menu:
            menuRutin();
            nodelay(stdscr, true);
            this->restoreStat();
            break;
    }
}

bool Engine::processCtlCall(){
    while(ctlCall.size() > 0){

		std::vector< variant<paraVarType> >currCall = ctlCall.front();

		int commd = currCall[0].get<svc>();
		switch(commd){
			case svc::loadEvent:
				evtCtl.pushEvent(currCall[1].get<std::string>());
				break;
			case svc::restoreStat:
				evtCtl.popEventStack();
				prom.discardMessage();
				this->restoreStat();
				break;
			case svc::setStat:
				this->setStat(currCall[1].get<Stats>());
				break;
			case svc::loadPrompt:
				prom.loadMessaage(currCall[1].get<wchar_t*>(), currCall[2].get<wchar_t*>());
				break;
			case svc::clearPrompt:
				prom.discardMessage();
				break;
			case svc::changeMap:
				mapCtl.setCurrentMap(currCall[1].get<std::string>());
				mapCtl.setPlayerPosition(Point(currCall[2].get<int>(), currCall[3].get<int>()));
				break;
            case svc::addItem:
                inv.addItem(currCall[1].get<std::string>(), currCall[2].get<int>());
                break;
            case svc::removeItem:
                inv.removeItem(currCall[1].get<std::string>(), currCall[2].get<int>());
                break;
            case svc::incItem:
                inv.incItem(currCall[1].get<std::string>());
                break;
            case svc::decItem:
                inv.decItem(currCall[1].get<std::string>());
                break;
			case svc::endGame:
				//recycleMem(ctlCall);
				return 0;
				break;
		}

		//for(unsigned int i = 0; i < currCall.size(); i++)
			//free(currCall[i]);

		ctlCall.pop_front();
    }

    return 1;
}

void Engine::updateScreen(){
    rdr.render_map(mapCtl.getCurrentMap());
    rdr.render_Player(mapCtl.getPlayer());
    if(prom.hasMessage()){
        rdr.render_prompt(prom);
    }

    rdr.update();
    return;
}

void Engine::menuRutin(){
    nodelay(stdscr, false); //Nasty Hack

    std::vector<std::string> mOption(3);
    mOption[0] = "Team";
    mOption[1] = "Inventory";
    mOption[2] = "Exit";

    unsigned int cursorPos = 0;

    for(;;){
        clear();

        //Make Frame and Print Title
        mvaddstr(0, 0, "================================================================================");
        for(int i = 1; i < 24; i++)mvaddch(i, 0, '|'),mvaddch(i, 79, '|');
        mvaddstr(24, 0, "===============================================================================");
        mvaddstr(2, 0, "================================================================================");
        for(int i = 3; i < 24; i++)mvaddch(i, 25, '|');

        //Print Useful Data
        mvaddstr(1, 38, "MENU");

        //Print All Options
        for(unsigned int i = 0; i < mOption.size(); i++)
            mvaddstr(4 + 2*i, 2, mOption[i].c_str());

        //Print Selected Options
        attron(A_BOLD);
        mvaddstr(4 + 2*cursorPos, 2, mOption[cursorPos].c_str());
        attroff(A_BOLD);

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
        clear();
        mvaddstr(0, 0, "================================================================================");
        for(int i = 1; i < 24; i++)mvaddch(i, 0, '|'),mvaddch(i, 79, '|');
        mvaddstr(24, 0, "===============================================================================");
        mvaddstr(2, 0, "================================================================================");
        for(int i = 3; i < 24; i++)mvaddch(i, 25, '|');
        mvaddstr(1, 35, "INVENTORY");

        std::vector<std::string> nameList = inv.getNameList(currentPos);

        if(nameList.size() == 0)
            continue;

        for (unsigned int i = 0; i < nameList.size(); i++){
            mvaddstr(i*2 + 4, 2, nameList[i].c_str());
        }

        //Print Selected Options
        attron(A_BOLD);
        mvaddstr(4, 2, nameList[0].c_str());
        attroff(A_BOLD);

        //Print Informations
        mvaddstr(4, 27, "Name:");
        mvaddstr(4, 33, inv[nameList[0]].item.getName().c_str());
        mvaddstr(6, 27, "Currently Have:");
        char tmp[10];
        sprintf(tmp, "%d", inv[nameList[0]].count);
        mvaddstr(6, 43, tmp);
        mvaddstr(8, 27, "Name:");
        mvaddstr(9, 33, inv[nameList[0]].item.getDescription().c_str());

        int c = getch();
        switch (c) {
            case KEY_UP:
                currentPos = (currentPos==0)? 0 : currentPos - 1;
                break;
            case KEY_DOWN:
                currentPos = (currentPos == nameList.size() - 1 )? nameList.size() - 1 : currentPos + 1;
                break;
            case 'z':

                break;
            case 'x':
            case 'q':
                return;
                break;
        }

    }

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

