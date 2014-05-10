#include "render.h"
#include "gmap.h"
#include "point.h"
#include <curses.h>
#include <locale>

render::render() : offset(0,0)
{
    scr = initscr();
    getmaxyx(scr, screen_max.m_y, screen_max.m_x);
}

render::~render()
{
    endwin();
}

void render::render_map(gmap toRender){
    clear();

    offset.m_x = screen_max.m_x / 2 - toRender.Getsize().m_x;
    offset.m_y = (screen_max.m_y - toRender.Getsize().m_y)/2;

    for(int i = 0; i < toRender.Getsize().m_y; i++){
        for(int j = 0; j < toRender.Getsize().m_x; j++){
            mvaddch(i + offset.m_y,j*2 + offset.m_x, toRender.Getdata()[i][j]);
        }
    }
    return;
}

void render::render_Player(objPlayer mo){
    mvaddch(mo.GetCord().Get_y() + offset.m_y, mo.GetCord().Get_x()*2 + offset.m_x, mo.Geticon());
    move(24,50);
}

void render::update(){
    refresh();
    return;
}
