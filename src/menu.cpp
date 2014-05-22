#include <curses.h>
#include <vector>
#include <string>
#include "menu.h"


/*void Menu::showMainMenu(){
    nodelay(stdscr, false); //Nasty Hack

    std::vector<std::string> mOption(3);
    mOption[0] = "Team";
    mOption[1] = "Inventory";
    mOption[2] = "Exit";



    for(;;){
        clear();

        //Make Frame and Print Title
        mvaddstr(0, 0, "================================================================================");
        for(int i = 1; i < 24; i++)mvaddch(i, 0, '|'),mvaddch(i, 79, '|');
        mvaddstr(24, 0, "===============================================================================");
        mvaddstr(2, 0, "================================================================================");
        for(int i = 3; i < 24; i++)mvaddch(i, 25, '|');

        //Print Useful Data
        mvaddstr(1, 38, "MENU");

        //Print All Options
        for(unsigned int i = 0; i < mOption.size(); i++)
            mvaddstr(4 + 2*i, 2, mOption[i].c_str());

        //Print Selected Options
        attron(A_BOLD);
        mvaddstr(4 + 2*cursorPos, 2, mOption[cursorPos].c_str());
        attroff(A_BOLD);

        //Wait User input
        int c = getch();
        switch (c) {
            case KEY_UP:
                cursorPos = (cursorPos==0)? mOption.size()-1 : cursorPos - 1;
                break;
            case KEY_DOWN:
                cursorPos = (cursorPos == mOption.size()-1)? 0 : cursorPos + 1;
                break;
            case 'z':
                switch(cursorPos){
                    case 0:
                        //teamMenuRoutin();
                        break;
                    case 1:
                        //invMenuRoutin();
                        break;
                    case 2:
                        prom.loadMessaage(L"Are You Sure?", L"System");
                        rdr.render_prompt(prom);
                        if(getch() == 'z'){
                            prom.loadMessaage(L"Bye", L"System");
                            rdr.render_prompt(prom);
                            getch();
                            ctlCall.push_back(loadStack(svc::endGame));
                            prom.discardMessage();
                            return;
                        }

                        break;
                }
                break;
            case 'x':
            case 'q':
                ctlCall.push_back(loadStack(svc::clearPrompt));
                return;
                break;
        }
    }
    return;
}

void Menu::showInvMenu(){

}

void Menu::showTeamMenu(){

}

void Engine::menuRutin(){

}

void Engine::invMenuRoutin(){
    unsigned int currentPos = 0;

    for(;;){
        clear();
        mvaddstr(0, 0, "================================================================================");
        for(int i = 1; i < 24; i++)mvaddch(i, 0, '|'),mvaddch(i, 79, '|');
        mvaddstr(24, 0, "===============================================================================");
        mvaddstr(2, 0, "================================================================================");
        mvaddstr(22, 26, "=====================================================");
        for(int i = 3; i < 24; i++)mvaddch(i, 25, '|');
        mvaddstr(1, 35, "INVENTORY");

        char mString[40];
        sprintf(mString, "Money: $%d", inv.getMoney());
        mvaddstr(23, 26, mString);

        std::vector<std::string> nameList = inv.getNameList(currentPos);

        if(nameList.empty()){
            while(getch()!='x');
            return;
        }

        for (unsigned int i = 0; i < nameList.size(); i++){
            mvaddstr(i*2 + 4, 2, nameList[i].c_str());
        }

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

        int c = getch();
        switch (c) {
            case KEY_UP:
                currentPos = (currentPos==0)? 0 : currentPos - 1;
                break;
            case KEY_DOWN:
                currentPos = (currentPos == nameList.size() - 1 )? nameList.size() - 1 : currentPos + 1;
                break;
            case 'z':
                //inv[nameList[0]].item
                break;
            case 'x':
            case 'q':
                return;
                break;
        }

    }

    return;
}

void Engine::teamMenuRoutin(){
        clear();
        mvaddstr(0, 0, "================================================================================");
        for(int i = 1; i < 24; i++)mvaddch(i, 0, '|'),mvaddch(i, 79, '|');
        mvaddstr(24, 0, "===============================================================================");
        mvaddstr(2, 0, "================================================================================");
        mvaddstr(1, 38, "TEAM");

        std::vector<std::string> memberList = team.getNameList();



        for (unsigned int i = 0; i < memberList.size(); i++){
            mvaddstr(3 + i * 5, 1, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            mvaddstr(3 + i * 5 + 5, 1, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

            char tmp[10];

            //Print Informations
            mvaddstr(3 + i * 5 + 1, 2, "Name:");
            mvaddstr(3 + i * 5 + 1, 8, team[memberList[i]].getName().c_str());

            mvaddstr(3 + i * 5 + 1, 25, "Level:");
            sprintf(tmp, "%d", team[memberList[i]].getLevel());
            mvaddstr(3 + i * 5 + 1, 32, tmp);

            mvaddstr(3 + i * 5 + 1, 40, "Role:");
            mvaddstr(3 + i * 5 + 1, 46, team[memberList[i]].getRole().getName().c_str());

            mvaddstr(3 + i * 5 + 2, 2, "HP:");
            sprintf(tmp, "%d", team[memberList[i]].getHP());
            mvaddstr(3 + i * 5 + 2, 6, tmp);
            sprintf(tmp, "/%d", team[memberList[i]].getRole().getMaxHP());
            addstr(tmp);

            mvaddstr(3 + i * 5 + 3, 2, "MP:");
            sprintf(tmp, "%d", team[memberList[i]].getHP());
            mvaddstr(3 + i * 5 + 3, 6, tmp);
            sprintf(tmp, "/%d", team[memberList[i]].getRole().getMaxHP());
            addstr(tmp);

            mvaddstr(3 + i * 5 + 2, 20, "EXP:");
            sprintf(tmp, "%d", team[memberList[i]].getExp());
            mvaddstr(3 + i * 5 + 2, 25, tmp);
            sprintf(tmp, "/%d", team[memberList[i]].getRole().getLevelUpExp());
            addstr(tmp);
        }

    while(getch()!='x');
    return;
}
*/
