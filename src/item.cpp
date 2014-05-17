#include "item.h"
#include <cstdlib>
#include "utils.h"
#include "json/value.h"
#include "json/reader.h"

Item::Item() : _id(0xffffffff), _name("NULL"), _description("NULL Item"), _price(0), _iscomsumable(0)
{
    //ctor
}

Item::Item(unsigned int id) : _id(id)
{
    char filename[256];
    sprintf(filename, "data/items/%d", id);
    std::string in = get_file_contents(filename);

    Json::Value root;
    Json::Reader reader;
    bool stat = reader.parse( in, root );
    if (stat){
        _name = root["Name"].asString();
        _description = root["Description"].asString();
        _price = root["Price"].asUInt();
        _iscomsumable = root["Comsumable"].asInt();
    }else{
        std::cout << "Failed to parse configuration\n"  << reader.getFormatedErrorMessages();
        exit(128);
    }
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
