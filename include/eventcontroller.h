#include <vector>
#include <deque>
#include "prompt.h"

#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

struct event{
    std::vector<std::string> stk;
    std::string trigBy;
};

class eventController
{
    public:
        eventController(std::deque<void*>&);
        ~eventController();

        int processInput(int c);

        void reversePushEventStack(event trig);
        void popEventStack();
        int execCurrentEvent();

    protected:
    private:
         std::vector<event> eventStack;
         std::deque<void*>& ctlCallStack;
};

#endif // EVENTCONTROLLER_H
