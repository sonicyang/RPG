#include <curses.h>
#include <vector>
#include <string>
#include <curses.h>
#include "menu.h"
#include "enum.h"
#include "itemexec.h"
#include "render.h"

int Menu::enterMenu(Team& team, inventory& inv, render& rdr){
    int t;

    for(t = showMainMenu(rdr); t!= -1; t = showMainMenu(rdr, t)){
        switch(t){
            case 0:
                for(int p = showTeamMenu(team, rdr); p != -1; p = showTeamMenu(team, rdr, p)){
                    for(int s = showCharMenu(team, p, rdr); s != -1; s = showCharMenu(team, p, rdr, s)){
                        if(s != 5){
                            inv.enableNull();
                            for(int k = showInvMenu(inv, rdr); k != -1; k = -1){
                                ItemExec::changeItem(inv, k, team, p, s, rdr);
                            }
                            inv.disableNull();
                        }else{
                            for(int k = showSkillMenu(team, p, rdr); k != -1; k = -1);
                        }
                    }
                }
                break;
            case 1:
                for(int p = showInvMenu(inv, rdr); p != -1; p = showInvMenu(inv, rdr, p)){
                    if(inv[inv.getNameList(p)[0]].item.isUsable()){
                        for(int s = showTeamMenu(team, rdr); s != -1; s = -1){
                            ItemExec::Exec(inv, p, team, s, rdr);
                        }
                    }else{
                        rdr.render_prompt(prompt(L"This Item is not Comsumable", L"System"));
                        getch();
                    }

                }
                break;
            case 2:
                rdr.render_prompt(prompt(L"Are You Sure?", L"System"));
                if(getch() == 'z'){
                    rdr.render_prompt(prompt(L"Bye", L"System"));
                    getch();
                    return 0;
                }
                break;
        }
    }
    return -1;
}

int Menu::showMainMenu(render& rdr, int curPos){
    unsigned int currentPos = curPos;

    std::vector<std::string> mOption;
    mOption.push_back("Team");
    mOption.push_back("Inventory");
    mOption.push_back("Exit");

    for(;;){
        rdr.render_MainMenu(currentPos, mOption);

        //Wait User input
        int c = getch();
        switch (c) {
            case KEY_UP:
                currentPos = (currentPos==0)? mOption.size()-1 : currentPos - 1;
                break;
            case KEY_DOWN:
                currentPos = (currentPos == mOption.size()-1)? 0 : currentPos + 1;
                break;
            case 'z':
                return currentPos;
                break;
            case 'x':
            case 'q':
                return -1;
                break;
        }
    }
    return -1;
}

int Menu::showTeamMenu(Team& team, render& rdr, int curPos){
    unsigned int currentPos = curPos;

    std::vector<std::string> memberList = team.getNameList();

    for(;;){
        rdr.render_TeamMenu(team, currentPos);

        int c = getch();
        switch (c) {
            case KEY_UP:
                currentPos = (currentPos==0)? 0 : currentPos - 1;
                break;
            case KEY_DOWN:
                currentPos = (currentPos == memberList.size() - 1 )? memberList.size() - 1 : currentPos + 1;
                break;
            case 'z':
                return currentPos;
                break;
            case 'x':
            case 'q':
                return -1;
                break;
        }

    }
    return -1;
}

int Menu::showCharMenu(Team& team, int index, render& rdr, int curPos){
    unsigned int currentPos = curPos;

    std::string cname = team.getNameList()[index];

    for(;;){
        rdr.render_CharMenu(team[cname], currentPos);

        int c = getch();
        switch (c) {
            case KEY_UP:
            case KEY_LEFT:
                currentPos = (currentPos==0)? 0 : currentPos - 1;
                break;
            case KEY_DOWN:
            case KEY_RIGHT:
                currentPos = (currentPos == 5 )? 5 : currentPos + 1;
                break;
            case 'z':
                return currentPos;
                break;
            case 'x':
            case 'q':
                return -1;
                break;
        }

    }

    return -1;
}


int Menu::showInvMenu(inventory& inv, render& rdr, int curPos){
    unsigned int currentPos = curPos;

    std::vector<std::string> nameList = inv.getNameList(currentPos);

    for(;;){
        rdr.render_InvMenu(inv, currentPos);

        if(nameList.empty()){
            while(getch()!='x');
            return -1;
        }

        int c = getch();
        switch (c) {
            case KEY_UP:
                currentPos = (currentPos==0)? 0 : currentPos - 1;
                break;
            case KEY_DOWN:
                currentPos = (currentPos == nameList.size() - 1 )? nameList.size() - 1 : currentPos + 1;
                break;
            case 'z':
                return currentPos;
                break;
            case 'x':
            case 'q':
                return -1;
                break;
        }

    }
    return -1;
}

int Menu::showSkillMenu(Team& team, int index, render& rdr){
    unsigned int currentPos = 0;

    std::string cname = team.getNameList()[index];

    for(;;){
        rdr.render_SkillMenu(team[cname], currentPos);

        if(team[cname].getSkillList().empty()){
            while(getch()!='x');
            return -1;
        }

        int c = getch();
        switch (c) {
            case KEY_UP:
                currentPos = (currentPos==0)? 0 : currentPos - 1;
                break;
            case KEY_DOWN:
                currentPos = (currentPos == team[cname].getSkillList().size() - 1 )? team[cname].getSkillList().size() - 1 : currentPos + 1;
                break;
            case 'z':
                return currentPos;
                break;
            case 'x':
            case 'q':
                return -1;
                break;
        }
    }

    return -1;
}
