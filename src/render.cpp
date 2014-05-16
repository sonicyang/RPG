#include <curses.h>
#include "render.h"
#include "gmap.h"
#include "point.h"

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
    mvaddstr(1, 1, "CurrentMap:");
    addstr(toRender.Getname().c_str());

    offset.m_x = screen_max.m_x / 2 - toRender.Getsize().m_x;
    offset.m_y = (screen_max.m_y - toRender.Getsize().m_y) / 2;

    for(unsigned int i = 0; i < toRender.Getsize().m_y; i++){
        for(unsigned int j = 0; j < toRender.Getsize().m_x; j++){
            if(toRender.Getdata()[i][j] < 128){
                mvaddch(i + offset.m_y, j*2 + offset.m_x, toRender.Getdata()[i][j]);
                insch(' ');
            }else{
                mvaddch(i + offset.m_y, j + offset.m_x, toRender.Getdata()[i][j]);
            }
        }
    }

    std::map<Point,mapObject>::const_iterator it = toRender.getObjects().begin();
    for(; it != toRender.getObjects().end(); it++){
        if(it->second.Geticon() < 128){
            mvaddch(it->first.m_y + offset.m_y, it->first.m_x + offset.m_x, it->second.Geticon());
            insch(' ');
        }else{
            mvaddch(it->first.m_y + offset.m_y, it->first.m_x + offset.m_x, it->second.Geticon());
        }

    }

    return;
}

void render::render_Player(objPlayer mo){
    if(offset.m_x, mo.Geticon() < 128){
        mvaddch(mo.GetCord().Get_y() + offset.m_y, mo.GetCord().Get_x() + offset.m_x, mo.Geticon());
        insch(' ');
    }else{
        mvaddch(mo.GetCord().Get_y() + offset.m_y, mo.GetCord().Get_x() + offset.m_x, mo.Geticon());
    }

    move(24,50);
    return;
}

void render::render_prompt(prompt P){
    attron(A_BOLD);
    mvaddstr(18, 0, "=========");
    mvaddstr(19, 0, "|       |");
    mvaddstr(20, 0, "================================================================================");
    mvaddstr(21, 0, "|                                                                              |");
    mvaddstr(22, 0, "|                                                                              |");
    mvaddstr(23, 0, "|                                                                              |");
    mvaddstr(24, 0, "================================================================================");
    attroff(A_BOLD);

    mvaddstr(19, 1, P.getWhom().c_str());
    mvaddstr(21, 1, P.getMessage().c_str());
    return;
}

void render::update(){
    refresh();
    return;
}
