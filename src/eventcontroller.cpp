#include "prompt.h"
#include <algorithm>
#include "utils.h"
#include <cstring>
#include "eventcontroller.h"
#include <curses.h>

using namespace std;

eventController::eventController(std::vector< std::vector<void*> >& s) : ctlCallStack(s)
{
}

eventController::~eventController()
{
    //dtor
}

int eventController::processInput(int c){
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
            execCurrentEvent();
            break;
        case 'x':{
            vector<void*> parmeters;
            parmeters.push_back(new int(0));
            ctlCallStack.push_back(parmeters);
            break;}
        case KEY_END:{
            vector<void*> parmeters;
            parmeters.push_back(new int(255));
            ctlCallStack.push_back(parmeters);
            break;}
    }
    return 1;
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
        vector<void*> parmeters;
        parmeters.push_back(new int(0));
        ctlCallStack.push_back(parmeters);
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
        case 1:{
            vector<void*> parmeters;
            parmeters.push_back(new int(1));
            parmeters.push_back(stringToAllocChar(ss[2]));
            parmeters.push_back(stringToAllocChar(ss[1]));
            ctlCallStack.push_back(parmeters);
            return 1;}
        case 2:{
            vector<void*> parmeters;
            parmeters.push_back(new int(2));
            ctlCallStack.push_back(parmeters);
            return 2;}
        case 3:{
            vector<void*> parmeters;
            parmeters.push_back(new int(3));
            parmeters.push_back(stringToAllocChar(ss[1]));
            parmeters.push_back(new int(atoi(ss[2].c_str())));
            parmeters.push_back(new int(atoi(ss[3].c_str())));
            ctlCallStack.push_back(parmeters);
            return 3;}
    }

    return 1;
}
