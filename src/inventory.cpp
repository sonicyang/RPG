#include "inventory.h"

inventory::inventory() : _inventorySlots(65536)
{
    //ctor
}

inventory::~inventory()
{
    //dtor
}

int inventory::incItem(unsigned int id){
    return addItem(id, 1);
}

int inventory::addItem(unsigned int id, unsigned int a){
    setItemAmount(id, getItemAmount(id) + a);
    return a;
}

int inventory::decItem(unsigned int id){
    return removeItem(id, 1);
}

int inventory::removeItem(unsigned int id, unsigned int a){
    unsigned int curr = getItemAmount(id);
    if(curr < a)
        return -1;
    setItemAmount(id, getItemAmount(id) - a);
    return a;
}

void inventory::setItemAmount(unsigned int id, unsigned int c){
    if(_inventorySlots[id].count == -1)
        _inventorySlots[id].item = Item(id);
    _inventorySlots[id].count = c;
    return;
}
unsigned int inventory::getItemAmount(unsigned int id){
    if(_inventorySlots[id].count == -1)
        return 0;
    return _inventorySlots[id].count;
}

unsigned int inventory::getNumOfItems(){
    int cc = 0;
    for(unsigned int i = 0; i < _inventorySlots.size(); i++){
        if(_inventorySlots[i].count != 0 && _inventorySlots[i].count != -1)
            cc++;
    }
    return cc;
}
