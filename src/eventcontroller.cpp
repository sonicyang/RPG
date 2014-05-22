#include <algorithm>
#include <cstring>
#include <curses.h>
#include "prompt.h"
#include "utils.h"
#include "eventcontroller.h"
#include "json/reader.h"
#include "json/value.h"
#include "utf8.h"

using namespace std;

eventController::eventController(std::string eventlist, std::deque< std::vector< variant<paraVarType> > >& s, std::map< std::string, variant<paraVarType> >& m) : ctlCallStack(s), varMap(m), userInputRequired(0)
{
	std::string in = get_file_contents(eventlist.c_str());

	Json::Value root;
	Json::Reader reader;
	if (reader.parse( in, root )){
	    event_count = root.get("Count", 0 ).asInt();
	    for(unsigned int i = 0; i < event_count; i++){
	            std::string in2 = get_file_contents(root["Path"][i].asCString());

	            Json::Value root2;
	            Json::Reader reader2;
	            if (reader.parse( in2, root2 )){
	            	event trigger;

	                trigger.stk.resize(root2["Command"].size());
	                for(unsigned int i = 0; i < root2["Command"].size(); i++){
	                    trigger.stk[i] = root2["Command"][i].asString();
	                }

	                trigger.trigBy = root2["Name"].asString();

	                trigger.triggerType = root2["triggerType"].asInt();

	                trigger.pc = 0;

	                event_list.insert (event_list.begin(), std::pair<std::string, event>(trigger.trigBy, trigger));
	            }else{
	                std::cout << "Failed to parse configuration\n"  << reader.getFormatedErrorMessages();
	                exit(128);
	            }
	    }

	}else{
	    std::cout << "Failed to parse configuration\n"  << reader.getFormatedErrorMessages();
	    exit(128);
	}
}

eventController::~eventController()
{
    //dtor
}

int eventController::processInput(int c){
    if(userInputRequired){
        switch (c) {
            case KEY_LEFT:

                break;
            case KEY_RIGHT:

                break;
            case KEY_UP:

                break;
            case KEY_DOWN:

                break;
            case 'z':
                execTopEvent();
                break;
            case 'x':
                ctlCallStack.push_back(loadStack(svc::restoreStat));
                break;
            case KEY_END:
                ctlCallStack.push_back(loadStack(svc::endGame));
                break;
        }
    }else{
        execTopEvent();
    }
    return 1;
}

void eventController::popEventStack(){
    if(eventStack.size() > 0){
        eventStack.pop_back();
    }
    return;
}

int eventController::execTopEvent(){
    struct event& currentEvent = eventStack.back();

    if(currentEvent.stk.size() == 0){
        ctlCallStack.push_back(loadStack(svc::restoreStat));
        return -1;
    }

    std::vector<std::string> ss = split(currentEvent.stk[currentEvent.pc], '|');

    int commd = atoi(ss[0].c_str());
    switch(commd){
        case 0:
            /*currBattle = battle(ss[1]);
            currBattle.exec();
            return 0;*/
        case eventCode::showPrompt:
            ctlCallStack.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar(ss[2].c_str()), UTF8_to_WChar(ss[1].c_str())));
            userInputRequired = 1;
            break;
        case eventCode::endEvent:
            ctlCallStack.push_back(loadStack(svc::clearPrompt));
            ctlCallStack.push_back(loadStack(svc::restoreStat));
            break;
        case eventCode::transferMap:
            ctlCallStack.push_back(loadStack(svc::changeMap, ss[1], atoi(ss[2].c_str()), atoi(ss[3].c_str())));
            userInputRequired = 0;
            break;
        case eventCode::addItem:
            ctlCallStack.push_back(loadStack(svc::addItem, ss[1], atoi(ss[2].c_str())));
            userInputRequired = 0;
            break;
        case eventCode::removeItem:
            ctlCallStack.push_back(loadStack(svc::removeItem, ss[1], atoi(ss[2].c_str())));
            userInputRequired = 0;
            break;
        case eventCode::setMoney:
            ctlCallStack.push_back(loadStack(svc::setMoney, atoi(ss[1].c_str())));
            userInputRequired = 0;
            break;
        case eventCode::addMoney:
            ctlCallStack.push_back(loadStack(svc::addMoney, atoi(ss[1].c_str())));
            userInputRequired = 0;
            break;
        case eventCode::jner:
            if(varMap[ss[1]].get<int>() != atoi(ss[2].c_str())){
                currentEvent.pc += atoi(ss[3].c_str());
                if(eventStack.back().pc >= currentEvent.stk.size())
                    throw(64);
            }
            userInputRequired = 0;
            break;
        case eventCode::jer:
            if(varMap[ss[1]].get<int>() == atoi(ss[2].c_str())){
                currentEvent.pc += atoi(ss[3].c_str());
                if(currentEvent.pc >= currentEvent.stk.size())
                    throw(64);
            }
            userInputRequired = 0;
            break;
        case eventCode::jne:
            if(varMap[ss[1]].get<int>() != atoi(ss[2].c_str())){
                currentEvent.pc = atoi(ss[3].c_str());
                if(eventStack.back().pc >= currentEvent.stk.size())
                    throw(64);
            }
            userInputRequired = 0;
            break;
        case eventCode::je:
            if(varMap[ss[1]].get<int>() == atoi(ss[2].c_str())){
                currentEvent.pc = atoi(ss[3].c_str());
                if(currentEvent.pc >= currentEvent.stk.size())
                    throw(64);
            }
            userInputRequired = 0;
            break;
    }

    currentEvent.pc++;
    return 1;
}

int eventController::pushEvent(std::string name){
	eventStack.push_back(event_list[name]);
	eventStack.back().pc = 0;
	userInputRequired = 0;
	return 0;
}
