#ifndef BATTLE_H
#define BATTLE_H

#include <curses.h>
#include <string>
#include <vector>
#include "inventory.h"
#include "team.h"
#include "monsterfactory.h"
#include "render.h"


class Battle
{
    public:
        Battle(std::string monsterList, std::deque< std::vector< variant<paraVarType> > >&, std::map< std::string, variant<paraVarType> >&);
        ~Battle();

        int processInput(int);

        int loadBattle(int memberCount, std::vector<std::string>& monsters, int chance = 0);

        int battleStart(std::vector<std::string>& monsters, int chance = 0);

        std::vector<Monster> getMonsters() { return _monsters; };
        int getMonsterTag() { return MonsterMenuCurrentPos; };
        int getCurrentChara() { return _currentChara; };
        int getMenuPos() { return battleMenuCurrentPos; };

        enum process{
            prePlayer = 0,
            playerDeathCheack,
            BattleMenu,
            MonsterMenu,
            PlayerNormalAttack,
            PrePlayerSkillQuery,
            PrePlayerSkill,
            PrePlayerSkill2,
            skillMonsterMenu,
            PlayerSkill,
            PostPlayer,
            PreMonsterTurn,
            MonsterTurn,
            TeamWipeOutCheck,
            PostBattle,
            Escaped
        };
    protected:
    private:
        std::deque< std::vector< variant<paraVarType> > >& ctlCallStack;
        std::map< std::string, variant<paraVarType> >& varMap;

        MonsterFactory _monsterCache;
        std::vector<Monster> _monsters;
        unsigned int _memberCount = 0;
        int _chance = 0;

        unsigned int _currentChara = 0;

        std::vector<int> charaAttackBuff;
        std::vector<int> charaDefenseBuff;

        int processPending;

        unsigned int battleMenuCurrentPos = 0;
        unsigned int MonsterMenuCurrentPos = 0;

        int battleMenu(int i);
        int monsterMenu();
        int useSkill(int i);
        bool isMonsterWipeOut();
        void calculateExp();
};

#endif // BATTLE_H
