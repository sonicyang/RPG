#include "battle.h"

#include <unistd.h>
#include <cstdlib>

#include "menu.h"
#include "itemexec.h"

Battle::Battle(std::string monsterList, inventory& inv, Team& team, render& rdrk) :
    _inv(inv),
    _team(team),
    rdr(rdrk),
    _monsterCache(monsterList)
{
    //ctor
}

Battle::~Battle()
{
    //dtor
}

int Battle::battleStart(std::vector<std::string>& monsters){

    for(unsigned int i = 0; i < monsters.size(); i++){
        _monsters.push_back(_monsterCache[monsters[i]]);
    }

    nodelay(stdscr, false);

    std::vector<std::string> memberList = _team.getNameList();

    for(;;){
        //player Movement
        for(unsigned int i = 0; i < memberList.size(); i++){
            rdr.render_BattleScene(_monsters);
            rdr.render_BattleTeam(_team, i);

            if(_team[memberList[i]].isDead())
                continue;

            int flag = 0;
            for(int k = battleMenu(); flag == 0; k = battleMenu()){
                rdr.render_BattleScene(_monsters);
                rdr.render_BattleTeam(_team, i);

                switch(k){
                    case 0:{
                        for(int p = monsterMenu(); p != -1; p = -1){
                            _monsters[p].varHP((-1)* _team[memberList[i]].getAttack());
                            flag = 1;
                        }
                        break;
                    }
                    case 1:{
                        for(int l = Menu::showSkillMenu(_team, i, rdr); l != -1; l = Menu::showSkillMenu(_team, i, rdr)){
                            Skill tmp = _team[memberList[i]].getSkillList()[l];
                            if(tmp.geteTarget() == 0){
                                for(int p = monsterMenu(); p != -1; p = -1){
                                    _monsters[p].varHP(tmp.geteHPv());
                                    _monsters[p].varMP(tmp.geteMPv());
                                    flag = 1;
                                }
                            }else if(tmp.geteTarget() == 1){
                                for(unsigned int m = 0; m < _monsters.size(); m++){
                                    _monsters[m].varHP(tmp.geteHPv());
                                    _monsters[m].varMP(tmp.geteMPv());
                                }
                                flag =1;
                            }

                            if(tmp.getfTarget() == 0){
                                for(int p = monsterMenu(); p != -1; p = -1){
                                    _team[memberList[i]].varHP(tmp.getfHPv());
                                    _team[memberList[i]].varMP(tmp.getfMPv());
                                    flag = 1;
                                }
                            }else if(tmp.getfTarget() == 1){
                                for(unsigned int m = 0; m < memberList.size(); m++){
                                    _team[memberList[m]].varHP(tmp.getfHPv());
                                    _team[memberList[m]].varMP(tmp.getfMPv());
                                }
                                flag =1;
                            }

                            if(flag)
                                break;
                        }
                        break;
                    }
                    case 2:{
                        for(int p = Menu::showInvMenu(_inv, rdr); p != -1; p = Menu::showInvMenu(_inv, rdr, p)){
                            if(_inv[_inv.getNameList(p)[0]].item.isUsable()){
                                for(int s = Menu::showTeamMenu(_team, rdr); s != -1; s = -1){
                                    ItemExec::Exec(_inv, p, _team, s, rdr);
                                    flag = 1;
                                }
                                if(flag)break;
                            }else{
                                rdr.render_prompt(prompt(L"This Item is not Comsumable", L"System"));
                                getch();
                            }
                        }
                        break;
                    }
                    case 3:{
                        break;
                    }
                }

                if(flag)
                    break;
            }

            rdr.render_BattleScene(_monsters);
            if(isMonsterWipeOut())
                break;
        }

        if(isMonsterWipeOut()){
            calculateExp();
            break;
        }


        //Monster Movement
        for(unsigned int i = 0; i < _monsters.size(); i++){
            rdr.render_BattleScene(_monsters);

            if(_monsters[i].isDead())
                continue;

            int target = rand() % memberList.size();

            _team[memberList[target]].varHP((-1) * _monsters[i].getAttack());

            usleep(1000000);

            rdr.render_BattleTeam(_team, i);
            if(_team.isWipeOut())
                break;
        }

        if(_team.isWipeOut())
            break;



    }

    nodelay(stdscr, true);

    _monsters.clear();
    return 0;
}

int Battle::battleMenu(){
    unsigned int currentPos = 0;

    for(;;){
        rdr.render_BattleMenu(currentPos);

        int c = getch();
        switch (c) {
            case KEY_UP:
                currentPos = (currentPos < 2)? currentPos : currentPos - 2;
                break;
            case KEY_DOWN:
                currentPos = (currentPos < 2)? currentPos + 2 : currentPos;
                break;
            case KEY_LEFT:
                currentPos = ((currentPos % 2) != 1)? currentPos : currentPos - 1;
                break;
            case KEY_RIGHT:
                currentPos = ((currentPos % 2) != 1)? currentPos + 1: currentPos;
                break;
            case 'z':
                return currentPos;
                break;
        }
    }
    return -1;
}

int Battle::monsterMenu(){
    unsigned int currentPos = 0;

    for(;;){
        rdr.render_BattleScene(_monsters, currentPos);

        int c = getch();
        switch (c) {
            case KEY_LEFT:
                currentPos = (currentPos==0)? _monsters.size()-1 : currentPos - 1;
                break;
            case KEY_RIGHT:
                currentPos = (currentPos == _monsters.size()-1)? 0 : currentPos + 1;
                break;
            case 'z':
                return currentPos;
                break;
            case 'x':
                return -1;
                break;
        }
    }
    return -1;
}

bool Battle::isMonsterWipeOut(){
    bool flag = true;
    for(unsigned int i = 0; i < _monsters.size(); i++){
        flag &= _monsters[i].isDead();
    }
    return flag;
}

void Battle::calculateExp(){
    for(unsigned int i = 0; i < _monsters.size(); i++){
        std::vector<std::string> memberList = _team.getNameList();
        for(unsigned int j = 0; j < memberList.size(); j++){
            _team[memberList[j]].varExp(_monsters[i].getExp());
        }
    }
}
