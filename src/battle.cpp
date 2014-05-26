#include "battle.h"

Battle::Battle(std::string monsterList, inventory& inv, Team& team, render& rdrk) :
    _inv(inv),
    _team(team),
    rdr(rdrk),
    _monsterCache(monsterList)
{
    //ctor
}

Battle::~Battle()
{
    //dtor
}

int Battle::battleStart(std::vector<std::string>& monsters){
    for(unsigned int i = 0; i < monsters.size(); i++){
        _monsters.push_back(_monsterCache[monsters[i]]);
    }



    _monsters.clear();
    return 0;
}
