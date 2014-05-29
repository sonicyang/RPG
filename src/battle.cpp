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
                            ctlCallStack.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar("You Failed to Escape!"), UTF8_to_WChar("System")));
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
        int dmg = (-1) * (rng) * (varMap["ret"].get<int>() + charaAttackBuff[_currentChara]) + _monsters[MonsterMenuCurrentPos].getDefense();


        _monsters[MonsterMenuCurrentPos].varHP(dmg);
        char kk[100];
        if(_monsters[MonsterMenuCurrentPos].isDead()){
            sprintf(kk, "%s is Dead!", _monsters[MonsterMenuCurrentPos].getName().c_str());
            _monsters.erase(_monsters.begin() + MonsterMenuCurrentPos);
        }else{
            sprintf(kk, "%s received %d point of damage!", _monsters[MonsterMenuCurrentPos].getName().c_str(), dmg);
        }
        ctlCallStack.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar(kk), UTF8_to_WChar("System")));

        processPending = process::PostPlayer;
    }else if(processPending == process::PrePlayerSkillQuery){
        if(varMap["SkillMenuCurPos"].get<unsigned int>() == 0xffffffff){
            processPending = process::BattleMenu;
        }else{
            std::string ss1;
            std::string ss2;

            ctlCallStack.push_back(loadStack(svc::qureySkillMonsterMenuRequired, _currentChara, varMap["SkillMenuCurPos"].get<unsigned int>()));
            ss1 = "eTarget";
            ss2 = "ret";
            ctlCallStack.push_back(loadStack(svc::moveVar, ss1, ss2));
            ctlCallStack.push_back(loadStack(svc::qureySkillTeamMenuRequired, _currentChara, varMap["SkillMenuCurPos"].get<unsigned int>()));
            ss1 = "fTarget";
            ss2 = "ret";
            ctlCallStack.push_back(loadStack(svc::moveVar, ss1, ss2));
            processPending = process::PrePlayerSkill;
        }
    }else if(processPending == process::PrePlayerSkill){
        if(varMap["eTarget"].get<int>() == 0){
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
        if(varMap["fTarget"].get<int>() == 0){
            ctlCallStack.push_back(loadStack(svc::loadTeamMenu, 1));
            ctlCallStack.push_back(loadStack(svc::setStat, Stats::inTeamMenu));
        }
        processPending = process::PlayerSkill;
    }else if(processPending == process::PlayerSkill){
        if(varMap["TeamMenuCurPos"].get<unsigned int>() == 0xffffffff){
            processPending = process::BattleMenu;
        }else{
            ctlCallStack.push_back(loadStack(svc::useSkill, _currentChara, varMap["SkillMenuCurPos"].get<unsigned int>(), MonsterMenuCurrentPos, varMap["TeamMenuCurPos"].get<unsigned int>()));
            processPending = process::PostPlayerSkill;
        }
    }else if(processPending == process::PostPlayerSkill){
        if(varMap["ret"].get<int>() == 0){
            ctlCallStack.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar("Not Enough Mana!"), UTF8_to_WChar("System")));
            processPending = process::BattleMenu;
        }else{
            processPending = process::PostPlayer;
        }
    }else if(processPending == process::PostPlayer){
        if(isMonsterWipeOut()){
            processPending = process::PostBattle;
        }else{
             _currentChara++;
            if(_currentChara >= _memberCount){
                processPending = process::PreMonsterTurn;
            }else{
                processPending = process::prePlayer;
            }
        }
    }else if(processPending == PreMonsterTurn){
        ctlCallStack.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar("It's Now Monster's Turn"), UTF8_to_WChar("System")));
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
            usleep(1000000);
        }

        ctlCallStack.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar("That Hurts..."), UTF8_to_WChar("System")));
        ctlCallStack.push_back(loadStack(svc::isTeamWipeOut));
        processPending = process::TeamWipeOutCheck;
    }else if(processPending == process::TeamWipeOutCheck){
        if(varMap["ret"].get<int>() != 1){
            ctlCallStack.push_back(loadStack(svc::loadPrompt, UTF8_to_WChar("It's Now your Turn"), UTF8_to_WChar("System")));
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
        ctlCallStack.push_back(loadStack(svc::restoreStat));
    }
    return 0;
}

bool Battle::isMonsterWipeOut(){
    bool flag = true;
    for(unsigned int i = 0; i < _monsters.size(); i++){
        flag &= _monsters[i].isDead();
    }
    return flag;
}
