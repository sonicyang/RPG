#ifndef ITEMEXEC_H
#define ITEMEXEC_H

#include <string>

#include "item.h"
#include "inventory.h"
#include "team.h"
#include "render.h"
#include "monster.h"

class ItemExec
{
    public:
        static int Exec(inventory& inv, int item, Team& team, int chara);
        static int changeItem(inventory& inv, int item, Team& team, int chara, int slot);
        static int skillExec(Team& _team, int chara, int skill, std::vector<Monster>& _monsters, int monsterId, int freindlyId);
    protected:
    private:
};

#endif // ITEMEXEC_H
