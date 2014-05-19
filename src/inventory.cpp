#include "inventory.h"

inventory::inventory() : _inventorySlots()
{
    null.count = -1;
    null.item = Item();
}

inventory::~inventory()
{
    //dtor
}

int inventory::incItem(std::string id){
    return addItem(id, 1);
}

int inventory::addItem(std::string id, unsigned int a){
    setItemAmount(id, getItemAmount(id) + a);
    return a;
}

int inventory::decItem(std::string id){
    return removeItem(id, 1);
}

int inventory::removeItem(std::string id, unsigned int a){
    unsigned int curr = getItemAmount(id);
    if(curr < a)
        return -1;
    setItemAmount(id, getItemAmount(id) - a);
    return a;
}

void inventory::setItemAmount(std::string id, unsigned int c){
    if(c == 0){
        _inventorySlots.erase(id);
        return;
    }
    if(_inventorySlots.find(id) == _inventorySlots.end())
        _inventorySlots[id].item = Item(id);
    _inventorySlots[id].count = c;
    return;
}
unsigned int inventory::getItemAmount(std::string id){
    if(_inventorySlots.find(id) == _inventorySlots.end())
        return 0;
    return _inventorySlots[id].count;
}

unsigned int inventory::getNumOfItems(){
    return _inventorySlots.size();
}

std::vector<std::string> inventory::getNameList(){
    std::vector<std::string> tmp;

    int i = 0;
    for (auto it = _inventorySlots.cbegin(); it != _inventorySlots.cend() && i < 10; it++){
        tmp.push_back((*it).first);
        i++;
    }

    return tmp;
}

const inventorySlot& inventory::operator[](std::string subscript){
    if(_inventorySlots.find(subscript) == _inventorySlots.end()){
        return null;
    }
    return _inventorySlots[subscript];
}
