#ifndef ITEMEXEC_H
#define ITEMEXEC_H

#include <string>

#include "item.h"
#include "inventory.h"
#include "team.h"
#include "render.h"

class ItemExec
{
    public:
        static int Exec(inventory& inv, int item, Team& team, int chara, render& rdr);
        static int changeItem(inventory& inv, int item, Team& team, int chara, render& rdr);
    protected:
    private:
};

#endif // ITEMEXEC_H
