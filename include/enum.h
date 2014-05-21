#ifndef ENUM_H_INCLUDED
#define ENUM_H_INCLUDED

#include <string>
#include <vector>

struct inventorySlot{
    Item item;
    int count = -1;
};

enum Stats{
    pending = 0,
    onMap,
    inEvent,
    menu
};

struct event{
    std::vector<std::string> stk;
    std::string trigBy;
    int triggerType;
};

enum trigType{
    buttonTrig = 1,
    stepOnTrig
};

enum faceing{
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
};

enum svc{
    loadEvent = -1,     // EventName
    restoreStat,        //
    setStat,            // stat Number
    loadPrompt,         // data, whom
    clearPrompt,        //
    changeMap,          // mapName, x, y
    addItem,            // id, amount
    removeItem,         //id, amount
    incItem,            //id
    decItem,            //id
    endGame = 255       //
};

enum eventCode{
    showPrompt = 1, // whom, data
    endEvent,
    transferMap, //  mapName, x, y
    grantItem
};

#endif // ENUM_H_INCLUDED
