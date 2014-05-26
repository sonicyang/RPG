#include "battle.h"

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
    std::vector<Monster> _monsters;
    for(unsigned int i = 0; i < monsters.size(); i++){
        _monsters.push_back(_monsterCache[monsters[i]]);
    }

    nodelay(false);


    std::vector<std::string> memberList = _team.getNameList();

    for(;;){
        rdr.render_BattleScene(_monsters);

        for(int i = 0; i< memberList.size(); i++){
            rdr.render_BattleTeam(team, i);

            unsigned int currentPos = 0;

            for(int c = getch(); c != 'z'; c = getch()){
                rdr.render_BattleMenu(currentPos);

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
                }
            }

            switch(currentPos){
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
            }


        }

    }

    nodelay(true);

    _monsters.clear();
    return 0;
}
