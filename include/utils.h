#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <fstream>
#include <string>
#include <cerrno>
#include <vector>
#include <deque>
#include "item.h"
#include "variant.h"
#include "enum.h"
#include "skill.h"

#define paraVarType int, unsigned int, wchar_t*, std::string, Stats, svc, std::vector<std::string>, Skill

char* stringToAllocChar(std::string);  //deceprated
void recycleMem(std::deque< std::vector<void*> >); //deceprated

template<typename... Args>
std::vector< variant<paraVarType> > loadStack(Args... args){
    std::vector< variant<paraVarType> > stk;

    loadStackR(stk, args...);

    return stk;
}

template<typename T, typename... Args>
void loadStackR(std::vector< variant<paraVarType> >& stk, T a, Args... args){
    variant<paraVarType> tmp;
    tmp.set<T>(a);
    stk.push_back(tmp);

    loadStackR(stk, args...);
    return;
}

template<typename T>
void loadStackR(std::vector< variant<paraVarType> >& stk, T a){
    variant<paraVarType> tmp;
    tmp.set<T>(a);
    stk.push_back(tmp);
    return;
}

inline void loadStackR(std::vector< variant<paraVarType> >& stk){
    return;
}

std::string get_file_contents(const char*);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

#endif // UTILS_H_INCLUDED
