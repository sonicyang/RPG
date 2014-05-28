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
/*
int Battle::battleStart(std::vector<std::string>& monsters, int chance){

    for(unsigned int i = 0; i < monsters.size(); i++){
        _monsters.push_back(_monsterCache[monsters[i]]);
    }

    nodelay(stdscr, false);

    std::vector<std::string> memberList = _team.getNameList();

    std::vector<int> charaAttackBuff(memberList.size(), 0);
    std::vector<int> charaDefenseBuff(memberList.size(), 0);

    for(;;){
        int stop = 0;

        //player Movement
        for(unsigned int i = 0; i < memberList.size(); i++){
            rdr.render_BattleScene(_monsters);
            rdr.render_BattleTeam(_team, i);

            //Dead Player can't attack
            if(_team[memberList[i]].isDead())
                continue;

            //Choose movement
            int flag = 0;
            for(int k = battleMenu(i); flag == 0; k = battleMenu(i)){

                switch(k){
                    case 0:{//Attack
                        for(int p = monsterMenu(); p != -1; p = -1){
                            float rng = (rand() % 6) / 10 + 0.75;
                            _monsters[p].varHP((-1) * (rng) * (_team[memberList[i]].getAttack() + charaAttackBuff[i]) + _monsters[p].getDefense());
                            flag = 1;
                        }
                        break;
                    }
                    case 1:{//Skill
                        useSkill(i);
                        break;
                    }
                    case 2:{//Inventory
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
                    case 3:{//Escape
                        int p = rand() % 100;
                        if(p - chance < 0){
                            stop = 1;
                        }
                        flag = 1;
                        break;
                    }
                }

                if(flag)
                    break;
            }

            if(isMonsterWipeOut())
                break;

            rdr.render_BattleScene(_monsters);
            rdr.render_BattleTeam(_team, i);
        }

        if(isMonsterWipeOut()){
            calculateExp();
            break;
        }

        if(stop == 1)
            break;


        //Monster Movement
        for(unsigned int i = 0; i < _monsters.size(); i++){
            rdr.render_BattleScene(_monsters);

            if(_monsters[i].isDead())
                continue;
            int us = rand() % _monsters[i].getSkillList().size() + 1;

            if(us == 0){//Normal Attack
                int target = rand() % memberList.size();
                float rng = (rand() % 6) / 10 + 0.75;
                _team[memberList[target]].varHP((-1) * (rng) * _monsters[i].getAttack() - _team[memberList[target]].getDefense() - charaDefenseBuff[target]);
            }else{//Skills
                Skill tmp = _monsters[i].getSkillList()[us - 1];

                if(tmp.getfTarget() == 0){
                    int target = rand() % _monsters.size();
                    _monsters[target].varHP(tmp.getfHPv());
                    _monsters[target].varMP(tmp.getfMPv());
                }else if(tmp.getfTarget() == 1){
                    for(unsigned int m = 0; m < _monsters.size(); m++){
                        _monsters[m].varHP(tmp.getfHPv());
                        _monsters[m].varMP(tmp.getfMPv());
                    }
                }

                if(tmp.geteTarget() == 0){
                    int target = rand() %  memberList.size();
                    _team[memberList[target]].varHP(tmp.geteHPv());
                }else if(tmp.geteTarget() == 1){
                    for(unsigned int m = 0; m < memberList.size(); m++){
                        _team[memberList[m]].varHP(tmp.geteHPv());
                        _team[memberList[m]].varMP(tmp.geteMPv());
                    }
                }
            }


            usleep(2000000);

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

int Battle::useSkill(int i){
    std::vector<std::string> memberList = _team.getNameList();
    int flag = 0;

    for(int l = Menu::showSkillMenu(_team, i, rdr); l != -1; l = Menu::showSkillMenu(_team, i, rdr)){
        rdr.render_BattleScene(_monsters);
        rdr.render_BattleMenu(1);
        rdr.render_BattleTeam(_team, i);

        flag = 0;

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
            flag = 1;
        }else if(tmp.geteTarget() == -1){
            flag = 1;
        }

        if(flag != 1)
            continue;

        if(tmp.getfTarget() == 0){
            for(int p = Menu::showTeamMenu(_team, rdr); p != -1; p = -1){
                _team[memberList[i]].varHP(tmp.getfHPv());
                _team[memberList[i]].varMP(tmp.getfMPv());
                flag = 2;
            }
        }else if(tmp.getfTarget() == 1){
            for(unsigned int m = 0; m < memberList.size(); m++){
                _team[memberList[m]].varHP(tmp.getfHPv());
                _team[memberList[m]].varMP(tmp.getfMPv());
            }
            flag = 2;
        }else if(tmp.getfTarget() == -1){
            flag = 2;
        }

        if(flag == 2)
            break;
    }

    return flag;
}

int Battle::battleMenu(int i){
    unsigned int currentPos = 0;

    for(;;){
        rdr.render_BattleScene(_monsters);
        rdr.render_BattleMenu(currentPos);
        rdr.render_BattleTeam(_team, i);

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
}*/
