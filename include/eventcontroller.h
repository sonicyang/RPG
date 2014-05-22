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
        eventController(std::string event_list, std::deque< std::vector< variant<paraVarType> > >&, std::map< std::string, variant<paraVarType> >&);
        ~eventController();

        int processInput(int c);

        void popEventStack();
        int execTopEvent();

        int pushEvent(std::string);

    protected:
    private:
        std::vector<event> eventStack;
        std::deque< std::vector< variant<paraVarType> > >& ctlCallStack;
        std::map< std::string, variant<paraVarType> >& varMap;

        std::map<std::string, event> event_list;
        unsigned event_count;

        int userInputRequired;


        //sspreate form the rest to avoid naming collison
        enum eventCode{
            showPrompt = 1, // whom, data       1
            endEvent,
            transferMap,//  mapName, x, y
            addItem,    //name val
            removeItem, //name val              5
            setMoney,   // val
            addMoney,   // val
            jner,       //name, val, addressR
            jer,        //name, val, addressR
            jne,        //name, val, address    10
            je,         //name, val, address
            mov,        //namedest, namesrc
            set,
            addCharToTeam,      //Name
            removeCharFromTeam  //Name          15
        };

};

#endif // EVENTCONTROLLER_H
