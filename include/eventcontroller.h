#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

#include <vector>
#include <deque>
#include <map>
#include "prompt.h"
#include "utils.h"
#include "variant.h"
#include "genericcontorller.h"

class Engine;

class eventController : public genericContorller
{
    public:
        eventController(std::string event_list, Engine*, std::map< std::string, variant<paraVarType> >&);
        virtual ~eventController();

        virtual int hDoEvent();

        void popEventStack();
        int execTopEvent();
        int pushEvent(std::string);

    protected:
    private:
        std::vector<event> eventStack;
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
            removeCharFromTeam,  //Name          15,
            battle,               //Name, Name, Name, Name
            vendor               //itemNames
        };

};

#endif // EVENTCONTROLLER_H
