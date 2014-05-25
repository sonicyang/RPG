#include "character.h"

Character::Character (RoleFactory* rf, std::string n, int lvl, Role role) : _roleCache(rf), _name(n), _exp(0), _role(role)
{
    _role.setLevel(lvl);
    _level = lvl;
    recoverHP();
    recoverMP();
}

Character::Character ()
{
    //dtor
}


Character::~Character (){
    //dtor
}

void Character::setHP(const int a){
    if(a >= 0 && a <= getMaxHP()){
        this->_hp = a;
    }else{
        this->_hp = getMaxHP();
    }
    return;
}

int Character::getHP() const{
    return this->_hp;
}

void Character::setMP(int a){
    if(a >= 0 && a <= getMaxMP()){
        this->_mp = a;
    }else{
        this->_mp = getMaxMP();
    }
    return;
}

int Character::getMP() const{
    return this->_mp;
}

void Character::setExp(const int a){
    if(a >= 0 && a < getLevelUpExp()){
        this->_exp = a;
    }else if(a >= 0 && a >= getLevelUpExp()){
        setExp(a - getLevelUpExp());
        //levelUp();
    }
    return;
}

int Character::getExp(void) const {
    return this->_exp;
}

int Character::getMaxHP(void) const {
    return _role.getMaxHP();
}

int Character::getMaxMP(void) const {
    return _role.getMaxMP();
}

int Character::getLevelUpExp(void) const {
    return _role.getLevelUpExp();
}

int Character::getAttack(void) const {
    return _role.getAttack();
}

int Character::getDefence(void) const {
    return _role.getDefence();
}

std::string Character::getRoleName(void) {
    return _role.getName();
}

void Character::recoverHP(void){
    setHP(_role.getMaxHP());
    return;
}

void Character::recoverMP(void){
    setMP(_role.getMaxMP());
    return;
}
