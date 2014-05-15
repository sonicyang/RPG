#include "controller.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include "gmap.h"
#include "point.h"
#include "utils.h"
#include "json/reader.h"
#include "json/value.h"
#include <string>
#include <curses.h>
#include "render.h"
#include <algorithm>

Controller::Controller() : rdr(), mapCtl("data/maps/maplist.lst", ctlCall), evtCtl("data/events/eventlist.lst", ctlCall)
{
}

Controller::~Controller()
{
}

void Controller::getParseUserInput(){
    int c = getch();
    switch(stat){
        case onMap:
            mapCtl.processInput(c);
            break;
        case inEvent:
            if(userInputPending){
                evtCtl.processInput(c);
            }else{
                evtCtl.execCurrentEvent();
            }
            break;
        case menu:
            menuRution();
            nodelay(stdscr, true);
            this->restoreStat();
            break;
    }
}

bool Controller::processCtlCall(){
    while(ctlCall.size() > 0){

		std::vector<void*>currCall = ctlCall.front();
		int commd = *(int*)(currCall[0]);
		switch(commd){
			case -1:
				evtCtl.execEvent(*(std::string*)(currCall[1]));
				userInputPending = 0;
				break;
			case 0:
				evtCtl.popEventStack();
				prom.discardMessage();
				this->restoreStat();
				userInputPending = 0;
				break;
			case 1:
				this->setStat(*(int*)(currCall[1]));
				userInputPending = 0;
				break;
			case 2:
				prom.loadMessaage((char*)(currCall[1]), (char*)(currCall[2]));
				userInputPending = 1;
				break;
			case 3:
				prom.discardMessage();
				userInputPending = 0;
				break;
			case 4:
				mapCtl.setCurrentMap((char*)(currCall[1]));
				mapCtl.setPlayerPosition(Point(*(int*)(currCall[2]), *(int*)(currCall[3])));
				userInputPending = 0;
				break;
			case 255:
				recycleMem(ctlCall);
				return 0;
				break;
		}

		for(int i = 0; i < currCall.size(); i++)
			delete [] currCall[i];

		ctlCall.pop_front();
    }

    return 1;
}

void Controller::updateScreen(){
    rdr.render_map(mapCtl.getCurrentMap());
    rdr.render_Player(mapCtl.getPlayer());
    if(prom.hasMessage()){
        rdr.render_prompt(prom);
    }

    rdr.update();
    return;
}

void Controller::menuRution(){
    nodelay(stdscr, false); //Nasty Hack

    std::vector<std::string> mOption(3);
    mOption[0] = "Team";
    mOption[1] = "Inventory";
    mOption[2] = "Exit";

    int cursorPos = 0;

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
        for(int i = 0; i < mOption.size(); i++)
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
                        prom.loadMessaage("Are You Sure?", "System");
                        rdr.render_prompt(prom);
                        if(getch() == 'z'){
                            prom.loadMessaage("Bye", "System");
                            rdr.render_prompt(prom);
                            getch();
                            ctlCall.push_back(loadStack(1, new int(255)));
                            ctlCall.push_back(loadStack(1, new int(255)));
                            prom.discardMessage();
                            return;
                        }

                        break;
                }
                break;
            case 'x':
            case 'q':
                return;
                break;
        }
    }
    return;
}



void Controller::setStat(int s){
    _stat.push_back(stat);
    stat = s;
    return;
}

void Controller::restoreStat(){
    if(_stat.size() > 0){
        stat = _stat.back();
        _stat.pop_back();
    }
    return;
}

