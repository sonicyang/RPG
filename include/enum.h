#ifndef ENUM_H_INCLUDED
#define ENUM_H_INCLUDED

#include <string>
#include <vector>

struct inventorySlot{
    Item item;
    int count = -1;
};

enum itemTypes{
    potion = 0,
    allPotion,
    head,
    armor,
    legs,
    shoes,
    weapon,
    null = -1
};

enum Stats{
    pending = 0,
    onMap,
    inEvent,
    inMainMenu,
    inTeamMenu,
    inInvMenu,
    inCharMenu,
    inSkillMenu
};

struct event{
    std::vector<std::string> stk;
    std::string trigBy;
    int triggerType;
    unsigned int pc;
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
    restoreStat,        //              0
    setStat,            // stat Number
    loadPrompt,         // data, whom
    clearPrompt,        //
    changeMap,          // mapName, x, y
    addItem,            // id, amount   5
    removeItem,         //id, amount
    incItem,            //id
    decItem,            //id
    setMoney,           //Amount
    addMoney,           //Amount        10
    addCharToTeam,      //Name
    removeCharFromTeam, //Name
    battle,
    loadMainMenu,
    loadTeamMenu,
    loadInvMenu,
    loadCharMenu,
    loadSkillMenu,
    invEnableNull,
    invDisableNull,
    changeEquip,        //itemIndex, memberIndex, slotIndex
    isItemUsable,       //itemIndex
    getItemType,        //itemIndex
    useItem,            //itemIndex, memberIndex
    endGame = 255       //
};

#endif // ENUM_H_INCLUDED
