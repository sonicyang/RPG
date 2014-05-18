#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "item.h"
#include "utils.h"

class inventory
{
    public:
        inventory();
        virtual ~inventory();

        int incItem(unsigned int);
        int addItem(unsigned int, unsigned int);
        int decItem(unsigned int);
        int removeItem(unsigned int, unsigned int);

        void setItemAmount(unsigned int, unsigned int);
        unsigned int getItemAmount(unsigned int);

        unsigned int getNumOfItems();

        const std::vector<inventorySlot>& getInventory() const { return _inventorySlots; };
    protected:
    private:
        std::vector<inventorySlot> _inventorySlots;
};

#endif // INVENTORY_H
