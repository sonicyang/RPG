#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include "item.h"

class inventory
{
    public:
        inventory();
        virtual ~inventory();
    protected:
    private:

        std::map<Item, unsigned int> _inventorySlots;
};

#endif // INVENTORY_H
