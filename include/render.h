#include "point.h"
#include "gmap.h"
#include "mapobject.h"
#include "objPlayer.h"
#include "prompt.h"
#include <curses.h>

#ifndef RENDER_H
#define RENDER_H


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

        void update();
    protected:
    private:
        WINDOW* scr;
        Point screen_max;
        Point offset;
};

#endif // RENDER_H

