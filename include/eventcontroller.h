#include <vector>


#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

struct event{
    std::vector<std::string> stk;
    std::string trigBy;
};

class eventController
{
    public:
        eventController();
        ~eventController();

        void pushEventStack(event trig);
        int execCurrentEvent();

    protected:
    private:
         vector<event> eventStack;
};

#endif // EVENTCONTROLLER_H
