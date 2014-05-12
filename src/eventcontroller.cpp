#include "prompt.h"
#include <algorithm>
#include "utils.h"
#include <cstring>
#include "eventcontroller.h"

eventController::eventController(std::deque<void*>& s) : ctlCallStack(s)
{
}

eventController::~eventController()
{
    //dtor
}


void eventController::reversePushEventStack(event trig){
    std::reverse(trig.stk.begin(), trig.stk.end());
    eventStack.push_back(trig);
    return;
}

void eventController::popEventStack(){
    if(eventStack.size() > 0){
        eventStack.pop_back();
    }
    return;
}

int eventController::execCurrentEvent(){
    if(eventStack.back().stk.size() == 0){
        ctlCallStack.push_front(new int(0));
        return -1;
    }

    std::vector<std::string> ss = split(eventStack.back().stk.back(), '|');
    eventStack.back().stk.pop_back();

    int commd = atoi(ss[0].c_str());
    switch(commd){
        case 0:
            /*currBattle = battle(ss[1]);
            currBattle.exec();
            return 0;*/
        case 1:
            ctlCallStack.push_front(stringToAllocChar(ss[1]));
            ctlCallStack.push_front(stringToAllocChar(ss[2]));
            ctlCallStack.push_front(new int(1));
            return 1;
        case 2:
            ctlCallStack.push_front(new int(2));
            return 2;
    }

    return 1;
}
