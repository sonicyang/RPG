#ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Monster
{
    public:
        Monster();
        Monster(std::string, int, int, int, int, int);
        virtual ~Monster();

        /* setters and getters */
        void setName(const std::string& val) { _name = val; };
        std::string getName(void) const { return _name; };

        void setHP(const int);
        int getHP(void) const;
        void varHP(const int);
        void setMP(const int);
        int getMP(void) const;
        void varMP(const int);

        int getExp(void) const { return _exp; };

        void recoverHP(void);
        void recoverMP(void);

        int getMaxHP(void);
        int getMaxMP(void);
        int getAttack(void);
        int getDefense(void);

    protected:
    private:

        std::string _name; // Stores the name of the player
        int max_hp; // stores max. HP of the player
        int max_mp;  // stores max. MP of the player
        int attack; // stores attack of the player
        int defense; // stores defense of the playe

        int _hp; // Stores the HP of the player, >= 0
        int _mp; // Stores the MP of the player, >= 0
        int _exp; // Stores the experience of the player, >= 0. Will not reset to zero after level-up


};

#endif // MONSTER_H
