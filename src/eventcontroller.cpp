#include "prompt.h"
#include <algorithm>
#include "utils.h"
#include "eventcontroller.h"

eventController::eventController(prompt& P) : pp(P)
{
}

eventController::~eventController()
{
    //dtor
}

void eventController::loadPrompt(prompt& P){
    pp = P;
    return;
}

void eventController::reversePushEventStack(event trig){
    std::reverse(trig.stk.begin(), trig.stk.end());
    eventStack.push_back(trig);
    return;
}

void eventController::popEventStack(){
    if(eventStack.size() > 0){
        eventStack.pop_back();
        pp.discardMessage();
    }
    return;
}

int eventController::execCurrentEvent(){
    if(eventStack.back().stk.size() == 0){
        return -1;
    }

    pp.discardMessage();

    std::vector<std::string> ss = split(eventStack.back().stk.back(), '|');
    eventStack.back().stk.pop_back();

    int commd = atoi(ss[0].c_str());
    switch(commd){
        case 0:
            /*currBattle = battle(ss[1]);
            currBattle.exec();
            return 0;*/
        case 1:
            pp.loadMessaage(ss[2], ss[1]);

            return 1;
    }

    return 1;
}
