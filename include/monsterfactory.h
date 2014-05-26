#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include <string>
#include "monster.h"

class MonsterFactory
{
    public:
        MonsterFactory(std::string monsterList);
        virtual ~MonsterFactory();

        Monster operator[](std::string val);
    protected:
    private:

        unsigned int _monsterCount;
        std::map<std::string, Monster> _monsterCache;

        Monster _null;
};

#endif // MONSTERFACTORY_H
