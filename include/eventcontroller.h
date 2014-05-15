#include <vector>
#include <deque>
#include <map>
#include "prompt.h"

#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

struct event{
    std::vector<std::string> stk;
    std::string trigBy;
    int triggerType;
};

enum trigType{
    buttonTrig = 1,
    stepOnTrig
};

class eventController
{
    public:
        eventController(std::string event_list, std::deque< std::vector<void*> >&);
        ~eventController();

        int processInput(int c);

        void reversePushEventStack(event trig);
        void popEventStack();
        int execCurrentEvent();

        int execEvent(std::string);

    protected:
    private:
         std::vector<event> eventStack;
         std::deque< std::vector<void*> >& ctlCallStack;

         std::map<std::string, event> event_list;
         unsigned event_count;

};

#endif // EVENTCONTROLLER_H
