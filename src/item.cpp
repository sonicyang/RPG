#include "item.h"

Item::Item() : _id(0xffffffff), _name("NULL"), _description("NULL Item"), _price(0), _iscomsumable(0)
{
    //ctor
}

Item::Item(unsigned int id) : _id(id)
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

bool Item::operator<(const Item& a) const{
    return _id < a._id;
}
bool Item::operator<=(const Item& a) const{
    return operator==(a) || operator<(a);
}
bool Item::operator>(const Item& a) const{
    return _id > a._id;
}
bool Item::operator>=(const Item& a) const{
    return operator==(a) || operator>(a);
}
bool Item::operator==(const Item& a) const{
    return _id == a._id;
}
bool Item::operator!=(const Item& a) const{
    return !operator==(a);
}
