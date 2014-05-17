#include "item.h"

Item::Item(std::string name, std::string des, int pri, bool com) : _name(name), _description(des), _price(pri), _iscomsumable(com)
{
    //ctor
}

Item::~Item()
{
    //dtor
}

Item::Item(const Item& other)
{
    _name = other._name;
    _description = other._description;
    _price = other._price;
    _iscomsumable = other._iscomsumable;
}

Item& Item::operator=(const Item& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
        _name = rhs._name;
        _description = rhs._description;
        _price = rhs._price;
        _iscomsumable = rhs._iscomsumable;
    return *this;
}
