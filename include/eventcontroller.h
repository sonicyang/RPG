#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

#include <vector>
#include <deque>
#include <map>
#include "prompt.h"
#include "utils.h"
#include "variant.h"

class eventController
{
    public:
        eventController(std::string event_list, std::deque< std::vector< variant<paraVarType> > >&);
        ~eventController();

        int processInput(int c);

        void popEventStack();
        int execTopEvent();

        int pushEvent(std::string);

    protected:
    private:
        std::vector<event> eventStack;
        std::deque< std::vector< variant<paraVarType> > >& ctlCallStack;

        std::map<std::string, event> event_list;
        unsigned event_count;

        int userInputRequired;


        //sspreate form the rest to avoid naming collison
        enum eventCode{
            showPrompt = 1, // whom, data
            endEvent,
            transferMap, //  mapName, x, y
            addItem,
            removeItem
        };

};

#endif // EVENTCONTROLLER_H
