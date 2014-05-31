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

        static void render_map(gmap, objPlayer);
        //static void render_Player(objPlayer);
        static void render_prompt(prompt& P);

        static void render_MainMenu(int curPos, std::vector<std::string> options);
        static void render_TeamMenu(Team&, unsigned int curPos);
        static void render_InvMenu(inventory& inv, int curPos);
        static void render_CharMenu(Character& chara, int curPos);
        static void render_SkillMenu(Character& chara, int curPos);

        static void render_BattleScene(std::vector<Monster> m, int tag = -1);
        static void render_BattleTeam(Team& team, unsigned int turn);
        static void render_BattleMenu(unsigned int curPos);

        static void render_VenderMenu(int curPos, std::vector<std::string> options);

        static void update();
    protected:
    private:

        static void mvaddutf8(int y, int x, wchar_t);
};

#endif // RENDER_H

