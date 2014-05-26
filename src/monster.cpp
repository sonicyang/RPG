#include "monster.h"

Monster::Monster()
{
    //ctor
}

Monster::Monster(std::string name, int hp, int mp, int atk, int def, int exp) :
    _name(name),
    max_hp(hp),
    max_mp(mp),
    attack(atk),
    defense(def),
    _exp(exp),
    _hp(max_hp),
    _mp(max_mp)
{
    //ctor
}

Monster::~Monster()
{
    //dtor
}

void Monster::setHP(const int a){
    if(a >= 0 && a <= getMaxHP()){
        this->_hp = a;
    }else{
        this->_hp = getMaxHP();
    }
    return;
}

int Monster::getHP() const{
    return this->_hp;
}

void Monster::varHP(const int val){
    setHP(getHP() + val);
    return;
}

void Monster::setMP(int a){
    if(a >= 0 && a <= getMaxMP()){
        this->_mp = a;
    }else{
        this->_mp = getMaxMP();
    }
    return;
}

int Monster::getMP() const{
    return this->_mp;
}

void Monster::varMP(const int val){
    setMP(getMP() + val);
    return;
}

int Monster::getExp(void) const {
    return this->_exp;
}

int Monster::getMaxHP(void) {
    return max_hp;
}

int Monster::getMaxMP(void) {
    return max_mp;
}

int Monster::getAttack(void) {
    return attack;
}

int Monster::getDefense(void) {
    return defense;
}

void Monster::recoverHP(void){
    setHP(max_hp);
    return;
}

void Monster::recoverMP(void){
    setMP(max_mp);
    return;
}
