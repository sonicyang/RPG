#define _XOPEN_SOURCE_EXTENDED

#include <curses.h>
#include "render.h"
#include "gmap.h"
#include "point.h"
#include <locale.h>

render::render() : offset(0,0)
{
    setlocale(LC_ALL, "");
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
    if(mo.Geticon() < 128){
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
    mvaddstr(screen_max.m_y - 7, 0, "=========");
    mvaddstr(screen_max.m_y - 6, 0, "|       |");
    for(unsigned int i = 0; i < screen_max.m_x ; i++)
        mvaddch(screen_max.m_y - 5, i, '=');

    for(int j = 4; j > 1; j--){
        mvaddch(screen_max.m_y - j, 0, '|');
        for(unsigned int i = 1; i < screen_max.m_x - 1; i++)mvaddch(screen_max.m_y - j, i, ' ');
        mvaddch(screen_max.m_y - j, screen_max.m_x - 1, '|');
    }

    for(unsigned int i = 0; i < screen_max.m_x ; i++)
        mvaddch(screen_max.m_y - 1, i, '=');
    attroff(A_BOLD);

    mvaddwstr(screen_max.m_y - 6, 1, P.getWhom().c_str());

    const wchar_t* inner = P.getMessage().c_str();
    unsigned int cur = 1;
    unsigned int line = 0;
    while((*inner) != 0){
        mvaddch(screen_max.m_y - 4 + line, cur, *inner);
        cur++;inner++;
        if(cur > screen_max.m_x - 2){
            cur = 1;
            line++;
        }
    }
    return;
}

void render::render_MainMenu(int curPos, std::vector<std::string> options){
    clear();

    //Make Frame and Print Title
    for(unsigned int i = 0; i < screen_max.m_x; i++)
        mvaddch(0, i, '=');
    for(unsigned int i = 1; i < screen_max.m_y; i++)mvaddch(i, 0, '|'),mvaddch(i, screen_max.m_x - 1, '|');
    for(unsigned int i = 0; i < screen_max.m_x; i++)
        mvaddch(screen_max.m_y - 1, i, '=');
    for(unsigned int i = 0; i < screen_max.m_x; i++)
        mvaddch(2, i, '=');
    for(unsigned int i = 3; i < screen_max.m_y; i++)mvaddch(i, 25, '|');

    mvaddstr(1, screen_max.m_x/2 - 2, "MENU");

    //Print All Options
    for(unsigned int i = 0; i < options.size(); i++)
        mvaddstr(4 + 2*i, 2, options[i].c_str());

    //Print Selected Options
    attron(A_BOLD);
    mvaddstr(4 + 2*curPos, 2, options[curPos].c_str());
    attroff(A_BOLD);
}

void render::render_TeamMenu(Team& team, unsigned int curPos){
    clear();

    //Make Frame and Print Title
    for(unsigned int i = 0; i < screen_max.m_x; i++)
        mvaddch(0, i, '=');
    for(unsigned int i = 1; i < screen_max.m_y; i++)mvaddch(i, 0, '|'),mvaddch(i, screen_max.m_x - 1, '|');
    for(unsigned int i = 0; i < screen_max.m_x; i++)
        mvaddch(screen_max.m_y - 1, i, '=');
    for(unsigned int i = 0; i < screen_max.m_x; i++)
        mvaddch(2, i, '=');

    mvaddstr(1, screen_max.m_x/2 - 2, "TEAM");

    std::vector<std::string> memberList = team.getNameList();

    for (unsigned int i = 0; i < memberList.size(); i++){
        if(i == curPos)
            attron(A_BOLD);

        //draw per frame
        for(unsigned int j = 1; j < screen_max.m_x - 1; j++){
            mvaddch(3 + i * 6, j, '~');
            mvaddch(3 + i * 6 + 5, j, '~');
        }

        char tmp[10];

        //Print Informations
        mvaddstr(3 + i * 6 + 1, 2, "Name:");
        mvaddstr(3 + i * 6 + 1, 8, team[memberList[i]].getName().c_str());

        mvaddstr(3 + i * 6 + 1, 25, "Level:");
        sprintf(tmp, "%d", team[memberList[i]].getLevel());
        mvaddstr(3 + i * 6 + 1, 32, tmp);

        mvaddstr(3 + i * 6 + 1, 40, "Role:");
        mvaddstr(3 + i * 6 + 1, 46, team[memberList[i]].getRole().getName().c_str());

        mvaddstr(3 + i * 6 + 2, 2, "HP:");
        sprintf(tmp, "%d", team[memberList[i]].getHP());
        mvaddstr(3 + i * 6 + 2, 6, tmp);
        sprintf(tmp, "/%d", team[memberList[i]].getRole().getMaxHP());
        addstr(tmp);

        mvaddstr(3 + i * 6 + 3, 2, "MP:");
        sprintf(tmp, "%d", team[memberList[i]].getHP());
        mvaddstr(3 + i * 6 + 3, 6, tmp);
        sprintf(tmp, "/%d", team[memberList[i]].getRole().getMaxHP());
        addstr(tmp);

        mvaddstr(3 + i * 6 + 2, 20, "EXP:");
        sprintf(tmp, "%d", team[memberList[i]].getExp());
        mvaddstr(3 + i * 6 + 2, 25, tmp);
        sprintf(tmp, "/%d", team[memberList[i]].getRole().getLevelUpExp());
        addstr(tmp);

        attroff(A_BOLD);
    }

}
void render::render_InvMenu(inventory& inv, int curPos){
    std::vector<std::string> nameList = inv.getNameList(curPos);

    clear();

    //Make Frame and Print Title
    for(unsigned int i = 0; i < screen_max.m_x; i++)
        mvaddch(0, i, '=');
    for(unsigned int i = 1; i < screen_max.m_y; i++)mvaddch(i, 0, '|'),mvaddch(i, screen_max.m_x - 1, '|');
    for(unsigned int i = 0; i < screen_max.m_x; i++)
        mvaddch(screen_max.m_y - 1, i, '=');
    for(unsigned int i = 0; i < screen_max.m_x; i++)
        mvaddch(2, i, '=');
    for(unsigned int i = 3; i < screen_max.m_y; i++)
        mvaddch(i, 25, '|');
    for(unsigned int i = 26; i < screen_max.m_x; i++)
        mvaddch(screen_max.m_y - 3, i, '=');

    mvaddstr(1, screen_max.m_x/2 - 5, "INVENTORY");

    char mString[40];
    sprintf(mString, "Money: $%d", inv.getMoney());
    mvaddstr(screen_max.m_y - 2, 28, mString);

    for (unsigned int i = 0; i < nameList.size(); i++){
        mvaddstr(i*2 + 4, 2, nameList[i].c_str());
    }

    if(!nameList.empty()){
        //Print Selected Options
        attron(A_BOLD);
        mvaddstr(4, 2, nameList[0].c_str());
        attroff(A_BOLD);

        //Print Informations
        mvaddstr(4, 27, "Name:");
        mvaddstr(4, 33, inv[nameList[0]].item.getName().c_str());
        mvaddstr(6, 27, "Currently Have:");
        char tmp[10];
        sprintf(tmp, "%d", inv[nameList[0]].count);
        mvaddstr(6, 43, tmp);
        mvaddstr(8, 27, "Description:");
        mvaddstr(9, 33, inv[nameList[0]].item.getDescription().c_str());
    }
}

void render::update(){
    refresh();
    return;
}

void render::mvaddutf8(int y, int x, wchar_t wc){
    /*cchar_t c;
    c.attr = 0;
    c.chars[0] = wc;
    c.chars[1] = L'\0';

    mvadd_wch(y, x, &c);*/
}

