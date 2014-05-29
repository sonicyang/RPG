#include "battle.h"

#include <unistd.h>
#include <cstdlib>

#include "enum.h"
#include "utf8.h"

Battle::Battle(std::string monsterList, std::deque< std::vector< variant<paraVarType> > >& a, std::map< std::string, variant<paraVarType> >& b) :
    ctlCallStack(a),
    varMap(b),
    _monsterCache(monsterList)
{
    //ctor
}

Battle::~Battle()
{
    //dtor
}

int Battle::loadBattle(int memberCount, std::vector<std::string>& monsters, int chance){
    _chance = chance;
    _memberCount = memberCount;
    _currentChara = 0;
    _monsters.clear();
    for(unsigned int i = 0; i < monsters.size(); i++){
        _monsters.push_back(_monsterCache[monsters[i]]);
    }
    charaAttackBuff.resize(memberCount);
    charaDefenseBuff.resize(memberCount);
    processPending = 0;
    return 0;
}

int Battle::processInput(int c){
    if(processPending == process::prePlayer){
        ctlCallStack.push_back(loadStack(svc::isCharDead, _currentChara)); //Query Death
        battleMenuCurrentPos = 0;
        processPending = process::playerDeathCheack;
    }else if(processPending == process::playerDeathCheack){
        if(varMap["ret"].get<int>() == 1){
            _currentChara++;
            if(_currentChara >= _memberCount){

            }else{
                processPending = process::prePlayer;
            }
        }else{
            processPending = process::BattleMenu;
        }
    }else if(processPending == process::BattleMenu){
        switch (c) {
            case KEY_UP:
                battleMenuCurrentPos = (battleMenuCurrentPos < 2)? battleMenuCurrentPos : battleMenuCurrentPos - 2;
                break;
            case KEY_DOWN:
                battleMenuCurrentPos = (battleMenuCurrentPos < 2)? battleMenuCurrentPos + 2 : battleMenuCurrentPos;
                break;
            case KEY_LEFT:
                battleMenuCurrentPos = ((battleMenuCurrentPos % 2) != 1)? battleMenuCurrentPos : battleMenuCurrentPos - 1;
                break;
            case KEY_RIGHT:
                battleMenuCurrentPos = ((battleMenuCurrentPos % 2) != 1)? battleMenuCurrentPos + 1: battleMenuCurrentPos;
                break;
            case 'z':
                switch(battleMenuCurrentPos){
                    case 0://Attack
                        processPending = MonsterMenu;
                        break;
                    case 1:
                        ctlCallStack.push_back(loadStack(svc::loadSkillMenu, 1));
                        ctlCallStack.push_back(loadStack(svc::setStat, Stats::inSkillMenu));
                        processPending = process::PrePlayerSkillQuery;
                        break;
                    case 2:
                        ctlCallStack.push_back(loadStack(svc::loadInvMenu, 0));
                        ctlCallStack.push_back(loadStack(svc::setStat, Stats::inInvMenu));
                        processPending = process::PostPlayer;
                        break;
                    case 3:
                        int p = rand() % 100;
                        if(p - _chance < 0){
                            ctlCallStack.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar("You Successfully Escaped!"), UTF8_to_WChar("System")));
                            processPending = process::Escaped;
                        }else{
                            processPending = process::PostPlayer;
                        }
                        break;
                }
                break;
            }
    }else if(processPending == process::MonsterMenu){
        switch (c) {
            case KEY_LEFT:
                MonsterMenuCurrentPos = (MonsterMenuCurrentPos==0)? _monsters.size() - 1 : MonsterMenuCurrentPos - 1;
                break;
            case KEY_RIGHT:
                MonsterMenuCurrentPos = (MonsterMenuCurrentPos == _monsters.size() - 1)? 0 : MonsterMenuCurrentPos + 1;
                break;
            case 'z':
                ctlCallStack.push_back((loadStack(svc::queryAttack, _currentChara)));
                processPending = process::PlayerNormalAttack;
                break;
            case 'x':
                processPending = process::BattleMenu;
                break;
        }
    }else if(processPending == process::PlayerNormalAttack){
        float rng = (rand() % 6) / 10 + 0.75;
        _monsters[MonsterMenuCurrentPos].varHP((-1) * (rng) * (varMap["ret"].get<int>() + charaAttackBuff[_currentChara]) + _monsters[MonsterMenuCurrentPos].getDefense());
        processPending = process::PostPlayer;
    }else if(processPending == process::PrePlayerSkillQuery){
        ctlCallStack.push_back(loadStack(svc::qureySkillMonsterMenuRequired, _currentChara, varMap["SkillMenuCurPos"].get<unsigned int>()));
        ctlCallStack.push_back(loadStack(svc::moveVar, "eTarget", "ret"));
        ctlCallStack.push_back(loadStack(svc::qureySkillTeamMenuRequired, _currentChara, varMap["SkillMenuCurPos"].get<unsigned int>()));
        ctlCallStack.push_back(loadStack(svc::moveVar, "fTarget", "ret"));
        processPending = process::PrePlayerSkill;
    }else if(processPending == process::PrePlayerSkill){
        if(varMap["eTarget"].get<int>() == 1){
            processPending = process::skillMonsterMenu;
        }else{
           processPending = process::PrePlayerSkill2;
        }
    }else if(processPending == process::skillMonsterMenu){
        switch (c) {
            case KEY_LEFT:
                MonsterMenuCurrentPos = (MonsterMenuCurrentPos==0)? _monsters.size() - 1 : MonsterMenuCurrentPos - 1;
                break;
            case KEY_RIGHT:
                MonsterMenuCurrentPos = (MonsterMenuCurrentPos == _monsters.size() - 1)? 0 : MonsterMenuCurrentPos + 1;
                break;
            case 'z':
                processPending = process::PrePlayerSkill2;
                break;
            case 'x':
                processPending = process::BattleMenu;
                break;
        }
    }else if(processPending == process::PrePlayerSkill2){
        if(varMap["fTarget"].get<int>() == 1){
            ctlCallStack.push_back(loadStack(svc::loadTeamMenu, 1));
            ctlCallStack.push_back(loadStack(svc::setStat, Stats::inTeamMenu));
        }
        processPending = process::PlayerSkill;
    }else if(processPending == process::PlayerSkill){
        ctlCallStack.push_back(loadStack(svc::useSkill, _currentChara, varMap["SkillMenuCurPos"].get<unsigned int>(), MonsterMenuCurrentPos, varMap["TeamMenuCurPos"].get<unsigned int>()));
        processPending = process::PostPlayer;
    }else if(processPending == process::PostPlayer){
        if(isMonsterWipeOut()){
            processPending = PostBattle;
        }else{
             _currentChara++;
            if(_currentChara >= _memberCount){
                processPending = process::PreMonsterTurn;
            }else{
                processPending = process::prePlayer;
            }
        }
    }else if(processPending == PreMonsterTurn){
        for (unsigned int i = 0; i < _memberCount; i++){
            ctlCallStack.push_back(loadStack(svc::queryDefense, i));
            char tmp[10];
            sprintf(tmp, "DEF%d", i);
            std::string ss(tmp);
            std::string ss2("ret");
            ctlCallStack.push_back(loadStack(svc::moveVar, ss, ss2));
        }
        processPending = process::MonsterTurn;
    }else if(processPending == process::MonsterTurn){
        for(unsigned int i = 0; i < _monsters.size(); i++){

            if(_monsters[i].isDead())
                continue;
            int us = rand() % _monsters[i].getSkillList().size() + 1;

            if(us == 0){//Normal Attack
                int target = rand() % _memberCount;
                float rng = (rand() % 6) / 10 + 0.75;

                char tmpk[10];
                sprintf(tmpk, "DEF%d", target);
                std::string ss(tmpk);

                ctlCallStack.push_back(loadStack(svc::varHP, target, ((-1) * (rng) * _monsters[i].getAttack() + varMap[ss].get<int>() + charaDefenseBuff[target])));

            }else{//Skills
                Skill tmp = _monsters[i].getSkillList()[us - 1];

                if(tmp.getfTarget() == 0){
                    _monsters[i].varHP(tmp.getfHPv());
                    _monsters[i].varMP(tmp.getfMPv());
                }else if(tmp.getfTarget() == 1){
                    for(unsigned int m = 0; m < _monsters.size(); m++){
                        _monsters[m].varHP(tmp.getfHPv());
                        _monsters[m].varMP(tmp.getfMPv());
                    }
                }

                if(tmp.geteTarget() == 0){
                    unsigned int target = rand() %  _memberCount;
                    ctlCallStack.push_back(loadStack(svc::varHP, target, tmp.geteHPv()));
                    ctlCallStack.push_back(loadStack(svc::varMP, target, tmp.geteMPv()));
                }else if(tmp.geteTarget() == 1){
                    for(unsigned int m = 0; m < _memberCount; m++){
                        ctlCallStack.push_back(loadStack(svc::varHP, m, tmp.geteHPv()));
                        ctlCallStack.push_back(loadStack(svc::varMP, m, tmp.geteMPv()));
                    }
                }
            }
            usleep(2000000);
        }

        ctlCallStack.push_back(loadStack(svc::isTeamWipeOut));
        processPending = process::TeamWipeOutCheck;
    }else if(processPending == process::TeamWipeOutCheck){
        if(varMap["ret"].get<int>() != 1){
            _currentChara = 0;
            processPending = process::prePlayer;
        }else{
            ctlCallStack.push_back(loadStack(svc::gameOver));
        }
    }else if(processPending == process::PostBattle){
        for(unsigned int i = 0; i < _monsters.size(); i++){
            for(unsigned int j = 0; j < _memberCount; j++){
                ctlCallStack.push_back(loadStack(svc::varExp, j, _monsters[i].getExp()));
            }
        }
        ctlCallStack.push_back(loadStack(svc::restoreStat));
    }else if(processPending == process::Escaped){
        ctlCallStack.push_back(loadStack(svc::clearPrompt));
        ctlCallStack.push_back(loadStack(svc::restoreStat));
    }
    return 0;
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




}*/


bool Battle::isMonsterWipeOut(){
    bool flag = true;
    for(unsigned int i = 0; i < _monsters.size(); i++){
        flag &= _monsters[i].isDead();
    }
    return flag;
}
