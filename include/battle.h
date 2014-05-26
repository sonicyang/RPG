#ifndef BATTLE_H
#define BATTLE_H

#include <curses.h>
#include <string>
#include <vector>
#include "inventory.h"
#include "team.h"
#include "monsterfactory.h"
#include "render.h"


class Battle
{
    public:
        Battle(std::string monsterList, inventory& inv, Team& team, render& rdrk);
        ~Battle();

        int battleStart(std::vector<std::string>& monsters);
    protected:
    private:
        inventory& _inv;
        Team& _team;
        render& rdr;

        std::vector<Monster> _monsters;
        MonsterFactory _monsterCache;
};

#endif // BATTLE_H
