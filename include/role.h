#ifndef ROLE_H
#define ROLE_H

#include <string>

class Role
{
    public:
        Role();
        Role(int, int, int, int, int, int, int, int);
        Role(int, int, int, int, int, int, int, int, int);
        virtual ~Role();

        int getMaxHP(void) const { return max_hp; };
        int getMaxMP(void) const { return max_mp; };
        int getLevelUpExp(void) const { return lvup_exp; };
        int getAttack(void) const { return attack; };
        int getDefence(void) const { return defense; };

        void setLevel(int);
    protected:
    private:
        int max_hp; // stores max. HP of the player
        int max_mp;  // stores max. MP of the player
        int lvup_exp; // stores needed experience to level-up
        int attack; // stores attack of the player
        int defense; // stores defense of the player

        int _hp_base, _hp_mpx;
        int _mp_base, _mp_mpx;
        int _attack_base, _attack_mpx;
        int _defense_base, _defense_mpx;
};

#endif // ROLE_H
