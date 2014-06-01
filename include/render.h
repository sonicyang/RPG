#ifndef RENDER_H
#define RENDER_H

#include <curses.h>
#include <SDL2/SDL.h>
#include "point.h"
#include "mapobject.h"
#include "inventory.h"
#include "team.h"
#include "character.h"
#include "monster.h"

class prompt;
class objPlayer;
class gmap;

class render
{
    public:
        render();
        ~render();

        void render_map(gmap, objPlayer);
        void render_prompt(prompt& P);

        void render_MainMenu(int curPos, std::vector<std::string> options);
        void render_TeamMenu(Team&, unsigned int curPos);
        void render_InvMenu(inventory& inv, int curPos);
        void render_CharMenu(Character& chara, int curPos);
        void render_SkillMenu(Character& chara, int curPos);

        void render_BattleScene(std::vector<Monster> m, int tag = -1);
        void render_BattleTeam(Team& team, unsigned int turn);
        void render_BattleMenu(unsigned int curPos);

        void render_VenderMenu(int curPos, std::vector<std::string> options);

        void render_StartMenu(int curPos, std::vector<std::string> options);
        void render_gameOver();
        void render_HelpMenu();

        void update();
    protected:
    private:
        SDL_Window *win = NULL;
        SDL_Renderer *ren = NULL;
};

#endif // RENDER_H

