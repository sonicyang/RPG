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

Engine::Engine() : rdr(), ctlCall(), mapCtl("data/maps/maplist.lst", ctlCall), evtCtl("data/events/eventlist.lst", ctlCall)
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
            menuRution();
            nodelay(stdscr, true);
            this->restoreStat();
            break;
    }
}

bool Engine::processCtlCall(){
    while(ctlCall.size() > 0){

		std::vector<void*>currCall = ctlCall.front();
		int commd = *(int*)(currCall[0]);
		switch(commd){
			case svc::loadEvent:
				evtCtl.pushEvent((char*)(currCall[1]));
				break;
			case svc::restoreStat:
				evtCtl.popEventStack();
				prom.discardMessage();
				this->restoreStat();
				break;
			case svc::setStat:
				this->setStat(*(int*)(currCall[1]));
				break;
			case svc::loadPrompt:
				prom.loadMessaage((wchar_t*)(currCall[1]), (wchar_t*)(currCall[2]));
				break;
			case svc::clearPrompt:
				prom.discardMessage();
				break;
			case svc::changeMap:
				mapCtl.setCurrentMap((char*)(currCall[1]));
				mapCtl.setPlayerPosition(Point(*(int*)(currCall[2]), *(int*)(currCall[3])));
				break;
            case svc::addItem:
                inv.addItem(*(unsigned int*)(currCall[1]), *(unsigned int*)(currCall[2]));
                break;
            case svc::removeItem:
                inv.removeItem(*(unsigned int*)(currCall[1]), *(unsigned int*)(currCall[2]));
                break;
            case svc::incItem:
                inv.incItem(*(unsigned int*)(currCall[1]));
                break;
            case svc::decItem:
                inv.decItem(*(unsigned int*)(currCall[1]));
                break;
			case svc::endGame:
				recycleMem(ctlCall);
				return 0;
				break;
		}

		for(unsigned int i = 0; i < currCall.size(); i++)
			free(currCall[i]);

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

void Engine::menuRution(){
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
                    case 2:
                        prom.loadMessaage(L"Are You Sure?", L"System");
                        rdr.render_prompt(prom);
                        if(getch() == 'z'){
                            prom.loadMessaage(L"Bye", L"System");
                            rdr.render_prompt(prom);
                            getch();
                            ctlCall.push_back(loadStack(1, new int(svc::endGame)));
                            prom.discardMessage();
                            return;
                        }

                        break;
                }
                break;
            case 'x':
            case 'q':
                ctlCall.push_back(loadStack(1, new int(svc::clearPrompt)));
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

