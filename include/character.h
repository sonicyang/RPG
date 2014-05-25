#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "role.h"
#include "rolefactory.h"
#include "item.h"

class Character
{
    public:
        Character();
        Character(RoleFactory*, std::string, int, Role);
        virtual ~Character();

        /* setters and getters */
        void setName(const std::string& val) { _name = val; };
        std::string getName(void) const { return _name; };

        void setHP(const int);
        int getHP(void) const;
        void setMP(const int);
        int getMP(void) const;
        void setExp(const int);
        int getExp(void) const;

        void recoverHP(void);
        void recoverMP(void);

        int getMaxHP(void) const;
        int getMaxMP(void) const;
        int getLevelUpExp(void) const;
        int getAttack(void) const;
        int getDefence(void) const;

        std::string getRoleName(void);
        //Role getRole(void) const { return _role; };

        void setLevel(const int); // call setAttr(int) to set attributes
        int getLevel(void) const { return _level; };

    protected:
    private:
        RoleFactory* _roleCache;

        std::string _name; // Stores the name of the player
        int _hp; // Stores the HP of the player, >= 0
        int _mp; // Stores the MP of the player, >= 0
        int _exp; // Stores the experience of the player, >= 0. Will not reset to zero after level-up
        int _level; // Stores the level of the player, >= 1

        Role _role;

        Item weapon;
        Item head;
        Item armor;
        Item legs;
        Item shoes;
};

#endif // CHARACTER _H
