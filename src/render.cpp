#define _XOPEN_SOURCE_EXTENDED

#include <curses.h>
#include <unistd.h>
#include "render.h"
#include "gmap.h"
#include "point.h"
#include <locale.h>
#include "Skill.h"

render::render()
{
}

render::~render()
{
}

void render::render_map(gmap toRender, objPlayer mo){
    clear();
    mvaddstr(1, 1, "CurrentMap:");
    addstr(toRender.Getname().c_str());

    Point offset;

    offset.m_x = getmaxx(stdscr) / 2 - toRender.Getsize().m_x;
    offset.m_y = (getmaxy(stdscr) - toRender.Getsize().m_y) / 2;

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

    if(mo.Geticon() < 128){
        mvaddch(mo.GetCord().Get_y() + offset.m_y, mo.GetCord().Get_x() + offset.m_x, mo.Geticon());
        insch(' ');
    }else{
        mvaddch(mo.GetCord().Get_y() + offset.m_y, mo.GetCord().Get_x() + offset.m_x, mo.Geticon());
    }

    return;
}

void render::render_prompt(prompt& P){
    attron(A_BOLD);
    mvaddstr(getmaxy(stdscr) - 7, 0, "=========");
    mvaddstr(getmaxy(stdscr) - 6, 0, "|       |");
    for(int i = 0; i < getmaxx(stdscr) ; i++)
        mvaddch(getmaxy(stdscr) - 5, i, '=');

    for(int j = 4; j > 1; j--){
        mvaddch(getmaxy(stdscr) - j, 0, '|');
        for(int i = 1; i < getmaxx(stdscr) - 1; i++)mvaddch(getmaxy(stdscr) - j, i, ' ');
        mvaddch(getmaxy(stdscr) - j, getmaxx(stdscr) - 1, '|');
    }

    for(int i = 0; i < getmaxx(stdscr) ; i++)
        mvaddch(getmaxy(stdscr) - 1, i, '=');
    attroff(A_BOLD);

    mvaddwstr(getmaxy(stdscr) - 6, 1, P.getWhom().c_str());

    const wchar_t* inner = P.getMessage().c_str();
    int cur = 1;
    unsigned int line = 0;
    while((*inner) != 0){
        mvaddch(getmaxy(stdscr) - 4 + line, cur, *inner);
        cur++;inner++;
        if(cur > getmaxx(stdscr) - 2){
            cur = 1;
            line++;
        }
    }
    return;
}

void render::render_MainMenu(int curPos, std::vector<std::string> options){
    clear();

    //Make Frame and Print Title
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(0, i, '=');
    for(int i = 1; i < getmaxy(stdscr); i++)mvaddch(i, 0, '|'),mvaddch(i, getmaxx(stdscr) - 1, '|');
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(getmaxy(stdscr) - 1, i, '=');
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(2, i, '=');
    for(int i = 3; i < getmaxy(stdscr); i++)mvaddch(i, 25, '|');

    mvaddstr(1, getmaxx(stdscr)/2 - 2, "MENU");

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
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(0, i, '=');
    for(int i = 1; i < getmaxy(stdscr); i++)mvaddch(i, 0, '|'),mvaddch(i, getmaxx(stdscr) - 1, '|');
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(getmaxy(stdscr) - 1, i, '=');
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(2, i, '=');

    mvaddstr(1, getmaxx(stdscr)/2 - 2, "TEAM");

    std::vector<std::string> memberList = team.getNameList();

    for (unsigned int i = 0; i < memberList.size(); i++){
        if(i == curPos)
            attron(A_BOLD);

        //draw per frame
        for(int j = 1; j < getmaxx(stdscr) - 1; j++){
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
        mvaddstr(3 + i * 6 + 1, 46, team[memberList[i]].getRoleName().c_str());

        mvaddstr(3 + i * 6 + 2, 2, "HP:");
        sprintf(tmp, "%d", team[memberList[i]].getHP());
        mvaddstr(3 + i * 6 + 2, 6, tmp);
        sprintf(tmp, "/%d", team[memberList[i]].getMaxHP());
        addstr(tmp);

        mvaddstr(3 + i * 6 + 3, 2, "MP:");
        sprintf(tmp, "%d", team[memberList[i]].getMP());
        mvaddstr(3 + i * 6 + 3, 6, tmp);
        sprintf(tmp, "/%d", team[memberList[i]].getMaxMP());
        addstr(tmp);

        mvaddstr(3 + i * 6 + 2, 20, "EXP:");
        sprintf(tmp, "%d", team[memberList[i]].getExp());
        mvaddstr(3 + i * 6 + 2, 25, tmp);
        sprintf(tmp, "/%d", team[memberList[i]].getLevelUpExp());
        addstr(tmp);

        attroff(A_BOLD);
    }

}

void render::render_InvMenu(inventory& inv, int curPos){
    std::vector<std::string> nameList = inv.getNameList(curPos);

    clear();

    //Make Frame and Print Title
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(0, i, '=');
    for(int i = 1; i < getmaxy(stdscr); i++)mvaddch(i, 0, '|'),mvaddch(i, getmaxx(stdscr) - 1, '|');
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(getmaxy(stdscr) - 1, i, '=');
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(2, i, '=');
    for(int i = 3; i < getmaxy(stdscr); i++)
        mvaddch(i, 25, '|');
    for(int i = 26; i < getmaxx(stdscr); i++)
        mvaddch(getmaxy(stdscr) - 3, i, '=');

    mvaddstr(1, getmaxx(stdscr)/2 - 5, "INVENTORY");

    char mString[40];
    sprintf(mString, "Money: $%d", inv.getMoney());
    mvaddstr(getmaxy(stdscr) - 2, 28, mString);

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

void render::render_CharMenu(Character& chara, int curPos){
    clear();

    //Make Frame and Print Title
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(0, i, '=');
    for(int i = 1; i < getmaxy(stdscr); i++)mvaddch(i, 0, '|'),mvaddch(i, getmaxx(stdscr) - 1, '|');
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(getmaxy(stdscr) - 1, i, '=');
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(2, i, '=');
    for(int i = 3; i < getmaxy(stdscr); i++)
        mvaddch(i, 25, '|');

    mvaddstr(1, (getmaxx(stdscr) - chara.getName().size())/2, chara.getName().c_str());


    char tmp[10];

    //Print Informations
    mvaddstr(4, 2, "Name:");
    mvaddstr(5, 4, chara.getName().c_str());

    mvaddstr(7, 2, "Level:");
    sprintf(tmp, "%d", chara.getLevel());
    mvaddstr(8, 4, tmp);

    mvaddstr(10, 2, "Role:");
    mvaddstr(11, 4, chara.getRoleName().c_str());

    mvaddstr(13, 2, "HP:");
    sprintf(tmp, "%d + ", chara.getBaseHP());
    mvaddstr(14, 4, tmp);
    sprintf(tmp, "%d", chara.getAdditionalHP());
    addstr(tmp);

    mvaddstr(16, 2, "MP:");
    sprintf(tmp, "%d + ", chara.getBaseMP());
    mvaddstr(17, 4, tmp);
    sprintf(tmp, "%d", chara.getAdditionalMP());
    addstr(tmp);

    mvaddstr(19, 2, "Attack:");
    sprintf(tmp, "%d + ", chara.getBaseAttack());
    mvaddstr(20, 4, tmp);
    sprintf(tmp, "%d", chara.getAdditionalAttack());
    addstr(tmp);

    mvaddstr(22, 2, "Defense:");
    sprintf(tmp, "%d + ", chara.getBaseDefense());
    mvaddstr(24, 4, tmp);
    sprintf(tmp, "%d", chara.getAdditionalDefense());
    addstr(tmp);

    if(curPos == 0)attron(A_BOLD);{
        mvaddstr(4, 27, "Head   : ");
        addstr(chara.getHead().getName().c_str());
    }attroff(A_BOLD);

    if(curPos == 1)attron(A_BOLD);{
        mvaddstr(5, 27, "Armor  : ");
        addstr(chara.getArmor().getName().c_str());
    }attroff(A_BOLD);

    if(curPos == 2)attron(A_BOLD);{
        mvaddstr(6, 27, "Legs   : ");
        addstr(chara.getLegs().getName().c_str());
    }attroff(A_BOLD);

    if(curPos == 3)attron(A_BOLD);{
        mvaddstr(7, 27, "Shoes  : ");
        addstr(chara.getShoes().getName().c_str());
    }attroff(A_BOLD);

    if(curPos == 4)attron(A_BOLD);{
        mvaddstr(9, 27, "Weapon : ");
        addstr(chara.getWeapon().getName().c_str());
    }attroff(A_BOLD);

    if(curPos == 5)attron(A_BOLD);{
        mvaddstr(15, 27, "Show Skills");
    }attroff(A_BOLD);
}

void render::render_SkillMenu(Character& chara, int curPos){
    clear();

    //Make Frame and Print Title
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(0, i, '=');
    for(int i = 1; i < getmaxy(stdscr); i++)mvaddch(i, 0, '|'),mvaddch(i, getmaxx(stdscr) - 1, '|');
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(getmaxy(stdscr) - 1, i, '=');
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(2, i, '=');
    for(int i = 3; i < getmaxy(stdscr); i++)
        mvaddch(i, 25, '|');

    mvaddstr(1, getmaxx(stdscr)/2 - 3, "Skills");

    std::vector<Skill> skills = chara.getSkillList();

    for(unsigned int i = 0; i < skills.size(); i++){
        mvaddstr(i*2 + 4, 2, skills[i].getName().c_str());
    }

    if(!skills.empty()){
        //Print Selected Options
        attron(A_BOLD);
        mvaddstr(4, 2, skills[0].getName().c_str());
        attroff(A_BOLD);

        //Print Informations
        mvaddstr(4, 27, "Name:");
        mvaddstr(5, 30, skills[0].getName().c_str());
        mvaddstr(8, 27, "Description:");
        mvaddstr(9, 30, skills[0].getDescription().c_str());
    }

}

void render::render_BattleScene(std::vector<Monster> m, int tag){
    clear();

    //Make Frame and Print Title
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(0, i, '=');
    for(int i = 1; i < getmaxy(stdscr); i++)mvaddch(i, 0, '|'),mvaddch(i, getmaxx(stdscr) - 1, '|');
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(getmaxy(stdscr) - 1, i, '=');

    int segment = getmaxx(stdscr) / (m.size() + 1);
    for(unsigned int i = 0; i < m.size(); i++){
        if((int)i == tag) attron(A_BOLD);
        mvaddstr((getmaxy(stdscr) - 8) / 2, (i + 1) * segment - m[i].getName().size()/2, m[i].getName().c_str());

        char tmp[10];
        sprintf(tmp, "%d/", m[i].getHP());
        mvaddstr((getmaxy(stdscr) - 8) / 2 + 1, (i + 1) * segment - m[i].getName().size()/2, tmp);
        sprintf(tmp, "%d", m[i].getMaxHP());
        addstr(tmp);

        attroff(A_BOLD);
    }
}

void render::render_BattleTeam(Team& team, unsigned int turn){
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(getmaxy(stdscr) - 8, i, '=');
    for(int i = getmaxy(stdscr) - 7; i < getmaxy(stdscr); i++)
        mvaddch(i, 30, '|');

    ::std::vector<std::string> nameList = team.getNameList();
    for(unsigned int i = 0; i < nameList.size(); i++){

        if(i == turn)attron(A_BOLD);{
            //Print Informations
            char tmp[10];

            mvaddstr(getmaxy(stdscr) - 6 + i, 2, team[nameList[i]].getName().c_str());

            sprintf(tmp, "%d/", team[nameList[i]].getHP());
            mvaddstr(getmaxy(stdscr) - 6 + i, 13, tmp);
            sprintf(tmp, "%d", team[nameList[i]].getMaxHP());
            addstr(tmp);

            sprintf(tmp, "%d/", team[nameList[i]].getMP());
            mvaddstr(getmaxy(stdscr) - 6 + i, 23, tmp);
            sprintf(tmp, "%d", team[nameList[i]].getMaxMP());
            addstr(tmp);

        }attroff(A_BOLD);
    }
}

void render::render_BattleMenu(unsigned int curPos){
    if(curPos == 0)attron(A_BOLD);{
        mvaddstr(getmaxy(stdscr) - 6, 32, "Attack");
    }attroff(A_BOLD);

    if(curPos == 1)attron(A_BOLD);{
        mvaddstr(getmaxy(stdscr) - 6, 42, "Skills");
    }attroff(A_BOLD);

    if(curPos == 2)attron(A_BOLD);{
        mvaddstr(getmaxy(stdscr) - 4, 32, "Inventory");
    }attroff(A_BOLD);

    if(curPos == 3)attron(A_BOLD);{
        mvaddstr(getmaxy(stdscr) - 4, 42, "Escape");
    }attroff(A_BOLD);
}

void render::render_VenderMenu(int curPos, std::vector<std::string> options){
    clear();

    //Make Frame and Print Title
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(0, i, '=');
    for(int i = 1; i < getmaxy(stdscr); i++)mvaddch(i, 0, '|'),mvaddch(i, getmaxx(stdscr) - 1, '|');
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(getmaxy(stdscr) - 1, i, '=');
    for(int i = 0; i < getmaxx(stdscr); i++)
        mvaddch(2, i, '=');
    for(int i = 3; i < getmaxy(stdscr); i++)
        mvaddch(i, 25, '|');

    mvaddstr(1, getmaxx(stdscr)/2 - 3, "Vendor");


    //Print All Options
    for(unsigned int i = 0; i < options.size(); i++)
        mvaddstr(4 + 2*i, 2, options[i].c_str());

    //Print Selected Options
    attron(A_BOLD);
    mvaddstr(4 + 2*curPos, 2, options[curPos].c_str());
    attroff(A_BOLD);
}

void render::render_StartMenu(int curPos, std::vector<std::string> options){
      clear();

      //Print All Options
      for(unsigned int i = 0; i < options.size(); i++)
          mvaddstr(16 + 2*i, 40 - options[i].size()/2, options[i].c_str());

      //Print Selected Options
      attron(A_BOLD);
      mvaddstr(16 + 2*curPos, 40 - options[curPos].size()/2, options[curPos].c_str());
      attroff(A_BOLD);
      refresh();
}

void render::render_gameOver(){
    clear();

    //Print Selected Options
    attron(A_BOLD);
    mvaddstr(getmaxy(stdscr) / 2, getmaxx(stdscr) / 2 - 4, "GameOver");
    attroff(A_BOLD);

    refresh();
    usleep(2000000);
    return;
}

void render::render_HelpMenu(){
    clear();

    //Make Frame and Print Title
    mvaddstr(0, 0, "================================================================================");
    for(int i = 1; i < 24; i++)mvaddch(i, 0, '|'),mvaddch(i, 79, '|');
    mvaddstr(24, 0, "===============================================================================");
    mvaddstr(2, 0, "================================================================================");

    //Print Title
    mvaddstr(1, 38, "HELP");

    mvaddstr(4, 2, "This is a Mini RPG Game");

    mvaddstr(8, 2, "Key Mapping:");
    mvaddstr(10, 2, "\t z - Select");
    mvaddstr(12, 2, "\t x - Cancel");
    mvaddstr(14, 2, "\t q - Menu");
    mvaddstr(16, 2, "\t Arrow Keys - Move");

   
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

