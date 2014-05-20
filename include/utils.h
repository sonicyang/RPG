#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <fstream>
#include <string>
#include <cerrno>
#include <vector>
#include <deque>
#include "item.h"
#include "variant.h"

union parament{
    int i;
    unsigned int ui;
    wchar_t* wcp;
    char* cp;
    std::string str;
};

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

char* stringToAllocChar(std::string);  //deceprated
void recycleMem(std::deque< std::vector<void*> >); //deceprated

template<typename... Args>
std::vector< variant<int, unsigned int, std::wstring, std::string> > loadStack(int n, Args... args){
    std::vector< variant<int, unsigned int, std::wstring, std::string> > stk;

    variant<int, unsigned int, std::wstring, std::string> tmp;
    tmp.set<int>(n);
    stk.push_back(tmp);

    if(sizeof...(Args) > 0)
        loadStackR(stk, args...);

    return stk;
}

template<typename T, typename... Args>
void loadStackR(std::vector< variant<int, unsigned int, std::wstring, std::string> >& stk, T a, Args... args){

    variant<int, unsigned int, std::wstring, std::string> tmp;
    tmp.set<T>(a);
    stk.push_back(tmp);

    loadStackR(stk, args...);

    return;
}

template<typename T>
void loadStackR(std::vector< variant<int, unsigned int, std::wstring, std::string> >& stk, T a){

    variant<int, unsigned int, std::wstring, std::string> tmp;
    tmp.set<T>(a);
    stk.push_back(tmp);

    return;
}

inline void loadStackR(std::vector< variant<int, unsigned int, std::wstring, std::string> >& stk){

    return;
}


std::string get_file_contents(const char*);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

#endif // UTILS_H_INCLUDED
