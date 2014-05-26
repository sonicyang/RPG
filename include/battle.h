#ifndef BATTLE_H
#define BATTLE_H

#include <curses.h>
#include <string>
#include <vector>
#include "inventory.h"
#include "team.h"


class Battle
{
    public:
        Battle(inventory& inv, Team& team);
        ~Battle();

        int battleStart(std::vector<std::string>& monsters);
    protected:
    private:
        inventory& _inv;
        Team& _team;
        std::vector<std::string> _monsters;

        MonsterFactory _monsterCache;


};

#endif // BATTLE_H
