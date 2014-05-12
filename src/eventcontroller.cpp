
#include "eventcontroller.h"

eventController::eventController()
{
    //ctor
}

eventController::~eventController()
{
    //dtor
}

void eventController::reversePushEventStack(event trig){
    std::reverse(trig.stk.begin(), trig.stk.end());
    eventStack.push_back(trig);
}

void eventController::popEventStack(){
    if(eventStack.size() > 0)
        eventStack.pop_back();
}



int eventController::execEvent(){
    if(eventStack.back().stk.size() == 0){
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
            prompt.whom = ss[1];
            prompt.prom = ss[2];
            return 1;
    }

    return 1;
}
