#include "character.h"

Character::Character ()
{

}

Character::Character (std::string n, int lvl, Role role) : _name(n), _exp(0), _role(role)
{
    _role.setLevel(lvl);
    _level = lvl;
    recoverHP();
    recoverMP();
}

Character::~Character ()
{
    //dtor
}

void Character::setHP(const int a){
    if(a >= 0 && a <= _role.getMaxHP()){
        this->_hp = a;
    }else{
        this->_hp = _role.getMaxHP();
    }
    return;
}

int Character::getHP() const{
    return this->_hp;
}

void Character::setMP(int a){
    if(a >= 0 && a <= _role.getMaxMP()){
        this->_mp = a;
    }else{
        this->_mp = _role.getMaxMP();
    }
    return;
}

int Character::getMP() const{
    return this->_mp;
}

void Character::setExp(const int a){
    if(a >= 0 && a < _role.getLevelUpExp()){
        this->_exp = a;
    }else if(a >= 0 && a >= _role.getLevelUpExp()){
        setExp(a - _role.getLevelUpExp());
        //levelUp();
    }
    return;
}

int Character::getExp(void) const {
    return this->_exp;
}

void Character::recoverHP(void){
    setHP(_role.getMaxHP());
    return;
}

void Character::recoverMP(void){
    setMP(_role.getMaxMP());
    return;
}
