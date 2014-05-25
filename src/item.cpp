#include <cstdlib>
#include <string>
#include "item.h"
#include "utils.h"
#include "json/value.h"
#include "json/reader.h"

Item::Item()
{
    //ctor
}

Item::Item(std::string name)
{
    char filename[256];
    sprintf(filename, "data/items/%s.item", name.c_str());
    std::string in = get_file_contents(filename);

    Json::Value root;
    Json::Reader reader;
    bool stat = reader.parse( in, root );
    if (stat){
        _name = root["Name"].asString();
        _description = root["Description"].asString();
        _id = root["ID"].asInt();
        _price = root["Price"].asUInt();
        _iscomsumable = root["Comsumable"].asInt();
        _type = root["Type"].asInt();

        _HPv = root.get("HPv", 0).asInt();
        _MPv = root.get("MPv", 0).asInt();
        _ATKv = root.get("ATKv", 0).asInt();
        _DEFv = root.get("DEFv", 0).asInt();
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
