#ifndef MENU_H
#define MENU_H

#include "team.h"
#include "inventory.h"
#include "render.h"

class Menu
{
    public:
        static int enterMenu(Team& team, inventory& inv, render& rdr);

        static int showMainMenu(render& rdr, int curPos = 0);
        static int showTeamMenu(Team& team, render& rdr, int curPos = 0);
        static int showCharMenu(Team& team, int index, render& rdr, int curPos = 0);
        static int showInvMenu(inventory& inv, render& rdr, int curPos = 0);

    protected:
    private:
};

#endif // MENU_H
