#ifndef RENDER_H
#define RENDER_H

#include <curses.h>
#include "point.h"
#include "gmap.h"
#include "mapobject.h"
#include "objPlayer.h"
#include "prompt.h"
#include "inventory.h"
#include "team.h"
#include "character.h"
#include "monster.h"

class render
{
    public:
        render();
        ~render();
        WINDOW* Getscr() { return scr; }
        Point Getscreen_max() { return screen_max; }

        void render_map(gmap);
        void render_Player(objPlayer);
        void render_prompt(prompt P);

        void render_MainMenu(int curPos, std::vector<std::string> options);
        void render_TeamMenu(Team&, unsigned int curPos);
        void render_InvMenu(inventory& inv, int curPos);
        void render_CharMenu(Character& chara, int curPos);

        void render_BattleScene(std::vector<Monster> m);
        void render_BattleTeam(Team& team, unsigned int turn);
        void render_BattleMenu(unsigned int curPos);

        void update();
    protected:
    private:
        WINDOW* scr;
        Point screen_max;
        Point offset;

        void mvaddutf8(int y, int x, wchar_t);
};

#endif // RENDER_H

