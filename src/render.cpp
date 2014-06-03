#define _XOPEN_SOURCE_EXTENDED

#include <iostream>
#include <unistd.h>
#include <locale.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "gmap.h"
#include "point.h"
#include "skill.h"
#include "prompt.h"
#include "gmap.h"

render::render()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        throw(122);
    }

    win = SDL_CreateWindow("RPG", 100, 100, WINDOW_SIZE_X, WINDOW_SIZE_Y,
                SDL_WINDOW_SHOWN);
    if (win == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        throw(122);
    }

    ren = SDL_CreateRenderer(win, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        throw(122);
    }

    TTF_Init();

    font = TTF_OpenFont(FONT_NAME.c_str(), 16);
}

render::~render()
{
    TTF_Quit();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void render::render_map(gmap toRender, mapObject mo){
    clear();

    Point offset;
    offset.m_x = (getmaxx() - toRender.Getsize().m_x * TILE_SIZE) / 2;
    offset.m_y = (getmaxy() - toRender.Getsize().m_y * TILE_SIZE) / 2;

    texture.loadFromFile(toRender.getTile(), ren);

    for(unsigned int i = 0; i < toRender.Getsize().m_y; i++){
       for(unsigned int j = 0; j < toRender.Getsize().m_x; j++){
           SDL_Rect ROI = {(int)toRender.Getdata_x()[i][j] * TILE_SIZE, (int)toRender.Getdata_y()[i][j] * TILE_SIZE, TILE_SIZE , TILE_SIZE};
           texture.render(ren, j * TILE_SIZE + offset.m_x, i * TILE_SIZE + offset.m_y, &ROI);
        }
    }

    std::map<Point,mapObject>::const_iterator it = toRender.getObjects().begin();
    for(; it != toRender.getObjects().end(); it++){
        texture.loadFromFile(it->second.getTile(), ren);
        SDL_Rect ROI = {(int)it->second.Geticon().m_x * TILE_SIZE, (int)it->second.Geticon().m_y * TILE_SIZE, TILE_SIZE , TILE_SIZE};
        texture.render(ren, it->second.GetCord().m_x * TILE_SIZE + offset.m_x, it->second.GetCord().m_y * TILE_SIZE + offset.m_y, &ROI);
    }

    texture.loadFromFile(mo.getTile(), ren);
    SDL_Rect ROI = {(int)mo.Geticon().m_x * TILE_SIZE, (int)mo.Geticon().m_y * TILE_SIZE, TILE_SIZE , TILE_SIZE};
    texture.render(ren, mo.GetCord().m_x * TILE_SIZE + offset.m_x, mo.GetCord().m_y * TILE_SIZE + offset.m_y, &ROI);

    font = TTF_OpenFont(FONT_NAME.c_str(), 16);

    char tmp[100];
    sprintf(tmp, "Current Map : %s", toRender.Getname().c_str());

    SDL_Color textColor = { 255, 255, 255  };
    texture.loadFromRenderedText(tmp, textColor, ren, font);
    texture.render(ren, 5, 5);

    update();
    return;
}

void render::render_prompt(prompt& P){
    texture.loadFromFile("data/menu/prompt.png", ren);
    texture.render(ren, 0, 400);

    font = TTF_OpenFont("data/font/Arial.ttf", 16);

    SDL_Color textColor = { 0xF4, 0xF0, 0xDD };
    texture.loadFromRenderedText(P.getWhom().c_str(), textColor, ren, font);
    texture.render(ren, 6, 425);

    unsigned int i;
    for(i = 65; P.getMessage().size() > i; i += 65){
        texture.loadFromRenderedText(P.getMessage().substr(i - 65, 65).c_str(), textColor, ren, font);
        texture.render(ren, 6, 465 + (i / 65 - 1) * 20);
    }

    texture.loadFromRenderedText(P.getMessage().substr(i-65, P.getMessage().size()).c_str(), textColor, ren, font);
    texture.render(ren, 6, 465 + (i / 65 - 1) * 20);

    update();
    return;
}

void render::render_MainMenu(int curPos, std::vector<std::string> options){
    clear();

    //Print Selected Options
    //attron(A_BOLD);
    mvaddstr(4 + 2*curPos, 2, options[curPos].c_str());
    //attroff(A_BOLD);


    texture.loadFromFile("data/menu/frame.png", ren);
    texture.render(ren, 0, 0);

    Point offset;
    offset.m_x = getmaxx() / 2;
    offset.m_y = getmaxy() / 2;

    SDL_Color textColor = {0xD8, 0xC6, 0x91};

    //Print Title
    font = TTF_OpenFont(FONT_NAME.c_str(), 50);
    texture.loadFromRenderedText("MENU", textColor, ren, font);
    texture.render(ren, offset.m_x - texture.getWidth() / 2, 5);

    font = TTF_OpenFont(FONT_NAME.c_str(), 32);
    for(unsigned int i = 0; i < options.size(); i++){
        texture.loadFromRenderedText(options[i].c_str(), textColor, ren, font);
        texture.render(ren, offset.m_x - texture.getWidth() / 2, offset.m_y - options.size() / 2 * texture.getHeight() + texture.getHeight() * i);
    }

    //Print Selected Options
    textColor = { 0xF4, 0xF0, 0xDD };
    texture.loadFromRenderedText(options[curPos].c_str(), textColor, ren, font);
    texture.render(ren, offset.m_x - texture.getWidth() / 2, offset.m_y - options.size() / 2 * texture.getHeight() + texture.getHeight() * curPos);


    update();
    return;
}

void render::render_TeamMenu(Team& team, unsigned int curPos){
    clear();

    //Make Frame and Print Title
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(0, i, '=');
    for(int i = 1; i < getmaxy(); i++)mvaddch(i, 0, '|'),mvaddch(i, getmaxx() - 1, '|');
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(getmaxy() - 1, i, '=');
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(2, i, '=');

    mvaddstr(1, getmaxx()/2 - 2, "TEAM");

    std::vector<std::string> memberList = team.getNameList();

    for (unsigned int i = 0; i < memberList.size(); i++){
        if(i == curPos)
            //attron(A_BOLD);

        //draw per frame
        for(int j = 1; j < getmaxx() - 1; j++){
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

        //attroff(A_BOLD);
    }

}

void render::render_InvMenu(inventory& inv, int curPos){
    std::vector<std::string> nameList = inv.getNameList(curPos);

    clear();

    //Make Frame and Print Title
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(0, i, '=');
    for(int i = 1; i < getmaxy(); i++)mvaddch(i, 0, '|'),mvaddch(i, getmaxx() - 1, '|');
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(getmaxy() - 1, i, '=');
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(2, i, '=');
    for(int i = 3; i < getmaxy(); i++)
        mvaddch(i, 25, '|');
    for(int i = 26; i < getmaxx(); i++)
        mvaddch(getmaxy() - 3, i, '=');

    mvaddstr(1, getmaxx()/2 - 5, "INVENTORY");

    char mString[40];
    sprintf(mString, "Money: $%d", inv.getMoney());
    mvaddstr(getmaxy() - 2, 28, mString);

    for (unsigned int i = 0; i < nameList.size(); i++){
        mvaddstr(i*2 + 4, 2, nameList[i].c_str());
    }

    if(!nameList.empty()){
        //Print Selected Options
        //attron(A_BOLD);
        mvaddstr(4, 2, nameList[0].c_str());
        //attroff(A_BOLD);

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
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(0, i, '=');
    for(int i = 1; i < getmaxy(); i++)mvaddch(i, 0, '|'),mvaddch(i, getmaxx() - 1, '|');
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(getmaxy() - 1, i, '=');
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(2, i, '=');
    for(int i = 3; i < getmaxy(); i++)
        mvaddch(i, 25, '|');

    mvaddstr(1, (getmaxx() - chara.getName().size())/2, chara.getName().c_str());


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

    if(curPos == 0)/*attron(A_BOLD)*/;{
        mvaddstr(4, 27, "Head   : ");
        addstr(chara.getHead().getName().c_str());
    }//attroff(A_BOLD);

    if(curPos == 1)/*attron(A_BOLD)*/;{
        mvaddstr(5, 27, "Armor  : ");
        addstr(chara.getArmor().getName().c_str());
    }//attroff(A_BOLD);

    if(curPos == 2)/*attron(A_BOLD)*/;{
        mvaddstr(6, 27, "Legs   : ");
        addstr(chara.getLegs().getName().c_str());
    }//attroff(A_BOLD);

    if(curPos == 3)/*attron(A_BOLD)*/;{
        mvaddstr(7, 27, "Shoes  : ");
        addstr(chara.getShoes().getName().c_str());
    }//attroff(A_BOLD);

    if(curPos == 4)/*attron(A_BOLD)*/;{
        mvaddstr(9, 27, "Weapon : ");
        addstr(chara.getWeapon().getName().c_str());
    }//attroff(A_BOLD);

    if(curPos == 5)/*attron(A_BOLD)*/;{
        mvaddstr(15, 27, "Show Skills");
    }//attroff(A_BOLD);
}

void render::render_SkillMenu(Character& chara, int curPos){
    clear();

    //Make Frame and Print Title
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(0, i, '=');
    for(int i = 1; i < getmaxy(); i++)mvaddch(i, 0, '|'),mvaddch(i, getmaxx() - 1, '|');
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(getmaxy() - 1, i, '=');
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(2, i, '=');
    for(int i = 3; i < getmaxy(); i++)
        mvaddch(i, 25, '|');

    mvaddstr(1, getmaxx()/2 - 3, "Skills");

    std::vector<Skill> skills = chara.getSkillList();

    for(unsigned int i = 0; i < skills.size(); i++){
        mvaddstr(i*2 + 4, 2, skills[i].getName().c_str());
    }

    if(!skills.empty()){
        //Print Selected Options
        //attron(A_BOLD);
        mvaddstr(4, 2, skills[0].getName().c_str());
        //attroff(A_BOLD);

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
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(0, i, '=');
    for(int i = 1; i < getmaxy(); i++)mvaddch(i, 0, '|'),mvaddch(i, getmaxx() - 1, '|');
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(getmaxy() - 1, i, '=');

    int segment = getmaxx() / (m.size() + 1);
    for(unsigned int i = 0; i < m.size(); i++){
        if((int)i == tag) //attron(A_BOLD);
        mvaddstr((getmaxy() - 8) / 2, (i + 1) * segment - m[i].getName().size()/2, m[i].getName().c_str());

        char tmp[10];
        sprintf(tmp, "%d/", m[i].getHP());
        mvaddstr((getmaxy() - 8) / 2 + 1, (i + 1) * segment - m[i].getName().size()/2, tmp);
        sprintf(tmp, "%d", m[i].getMaxHP());
        addstr(tmp);

        //attroff(A_BOLD);
    }
}

void render::render_BattleTeam(Team& team, unsigned int turn){
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(getmaxy() - 8, i, '=');
    for(int i = getmaxy() - 7; i < getmaxy(); i++)
        mvaddch(i, 30, '|');

    std::vector<std::string> nameList = team.getNameList();
    for(unsigned int i = 0; i < nameList.size(); i++){

        if(i == turn)/*attron(A_BOLD)*/;{
            //Print Informations
            char tmp[10];

            mvaddstr(getmaxy() - 6 + i, 2, team[nameList[i]].getName().c_str());

            sprintf(tmp, "%d/", team[nameList[i]].getHP());
            mvaddstr(getmaxy() - 6 + i, 13, tmp);
            sprintf(tmp, "%d", team[nameList[i]].getMaxHP());
            addstr(tmp);

            sprintf(tmp, "%d/", team[nameList[i]].getMP());
            mvaddstr(getmaxy() - 6 + i, 23, tmp);
            sprintf(tmp, "%d", team[nameList[i]].getMaxMP());
            addstr(tmp);

        }//attroff(A_BOLD);
    }
}

void render::render_BattleMenu(unsigned int curPos){
    if(curPos == 0)/*attron(A_BOLD)*/;{
        mvaddstr(getmaxy() - 6, 32, "Attack");
    }//attroff(A_BOLD);

    if(curPos == 1)/*attron(A_BOLD)*/;{
        mvaddstr(getmaxy() - 6, 42, "Skills");
    }//attroff(A_BOLD);

    if(curPos == 2)/*attron(A_BOLD)*/;{
        mvaddstr(getmaxy() - 4, 32, "Inventory");
    }//attroff(A_BOLD);

    if(curPos == 3)/*attron(A_BOLD)*/;{
        mvaddstr(getmaxy() - 4, 42, "Escape");
    }//attroff(A_BOLD);
}

void render::render_VenderMenu(int curPos, std::vector<std::string> options){
    clear();

    //Make Frame and Print Title
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(0, i, '=');
    for(int i = 1; i < getmaxy(); i++)mvaddch(i, 0, '|'),mvaddch(i, getmaxx() - 1, '|');
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(getmaxy() - 1, i, '=');
    for(int i = 0; i < getmaxx(); i++)
        mvaddch(2, i, '=');
    for(int i = 3; i < getmaxy(); i++)
        mvaddch(i, 25, '|');

    mvaddstr(1, getmaxx()/2 - 3, "Vendor");


    //Print All Options
    for(unsigned int i = 0; i < options.size(); i++)
        mvaddstr(4 + 2*i, 2, options[i].c_str());

    //Print Selected Options
    //attron(A_BOLD);
    mvaddstr(4 + 2*curPos, 2, options[curPos].c_str());
    //attroff(A_BOLD);
}

void render::render_StartMenu(int curPos, std::vector<std::string> options){
    clear();
    texture.loadFromFile("data/menu/frame_title.png", ren);
    texture.render(ren, 0, 0);

    font = TTF_OpenFont(FONT_NAME.c_str(), 36);

    Point offset;
    offset.m_x = getmaxx() / 2;
    offset.m_y = getmaxy() / 2;

    SDL_Color textColor = {0xD8, 0xC6, 0x91};

    texture.loadFromRenderedText("This is a Mini RPG Game", textColor, ren, font);
    texture.render(ren, offset.m_x - texture.getWidth() / 2, 100);

    font = TTF_OpenFont(FONT_NAME.c_str(), 24);

    //Print All Options
    for(unsigned int i = 0; i < options.size(); i++){
        texture.loadFromRenderedText(options[i].c_str(), textColor, ren, font);
        texture.render(ren, offset.m_x - texture.getWidth() / 2, offset.m_y + (i - 1) * 40);
    }

    //Print Selected Options
    textColor = { 0xF4, 0xF0, 0xDD };
    texture.loadFromRenderedText(options[curPos].c_str(), textColor, ren, font);
    texture.render(ren, offset.m_x - texture.getWidth() / 2, offset.m_y + (curPos - 1) * 40);

    update();
    return;
}

void render::render_gameOver(){
    clear();

    texture.loadFromFile("data/menu/frame_title.png", ren);
    texture.render(ren, 0, 0);

    Point offset;
    offset.m_x = getmaxx() / 2;
    offset.m_y = getmaxy() / 2;

    font = TTF_OpenFont(FONT_NAME.c_str(), 36);

    SDL_Color textColor = { 0xF4, 0xF0, 0xDD };
    texture.loadFromRenderedText("GameOver", textColor, ren, font);
    texture.render(ren, offset.m_x - texture.getWidth() / 2, offset.m_y - texture.getHeight() / 2);

    usleep(2000000);
    update();
    return;
}

void render::render_HelpMenu(){
    clear();

    texture.loadFromFile("data/menu/frame.png", ren);
    texture.render(ren, 0, 0);

    Point offset;
    offset.m_x = getmaxx() / 2;
    offset.m_y = getmaxy() / 2;

    SDL_Color textColor = {0xD8, 0xC6, 0x91};

    //Print Title
    font = TTF_OpenFont(FONT_NAME.c_str(), 50);
    texture.loadFromRenderedText("HELP", textColor, ren, font);
    texture.render(ren, offset.m_x - texture.getWidth() / 2, 5);

    texture.loadFromRenderedText("This is a Mini RPG Game", textColor, ren, font);
    texture.render(ren, offset.m_x - texture.getWidth() / 2, 100);

    font = TTF_OpenFont(FONT_NAME.c_str(), 32);
    texture.loadFromRenderedText("Key Mapping:", textColor, ren, font);
    texture.render(ren, offset.m_x - texture.getWidth() / 2, 200);
    texture.loadFromRenderedText("Select -- z or Enter", textColor, ren, font);
    texture.render(ren, offset.m_x - texture.getWidth() / 2, 250);
    texture.loadFromRenderedText("Cancel -- x", textColor, ren, font);
    texture.render(ren, offset.m_x - texture.getWidth() / 2, 300);
    texture.loadFromRenderedText("Menu -- q or ESC", textColor, ren, font);
    texture.render(ren, offset.m_x - texture.getWidth() / 2, 350);
    texture.loadFromRenderedText("Move -- Arrow Keys", textColor, ren, font);
    texture.render(ren, offset.m_x - texture.getWidth() / 2, 400);

    update();
}

void render::update(){
    SDL_RenderPresent(ren);
    return;
}

void render::clear(){
    SDL_RenderClear(ren);
    return;
}

void render::mvaddstr(int y, int x, const char* str){
    _currX = x;
    _currY = y;

    SDL_Color textColor = { 255, 255, 255  };
    texture.loadFromRenderedText(str, textColor, ren, font);

    texture.render(ren, x * 10, y * 10);
    return;
}

void render::addstr (const char*){

}

void render::mvaddch(int y, int x, char){

}

void render::mvaddch(int y, int x, wchar_t){

}

void render::mvaddwstr(int y, int x, const wchar_t*){

}
