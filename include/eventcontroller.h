#include <vector>
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
        eventController(prompt& P);
        ~eventController();

        void reversePushEventStack(event trig);
        void popEventStack();
        int execCurrentEvent();

        void loadPrompt(prompt& P);

    protected:
    private:
         std::vector<event> eventStack;
         prompt& pp;
};

#endif // EVENTCONTROLLER_H
