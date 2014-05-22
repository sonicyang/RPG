#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "utils.h"

class inventory
{
    public:
        inventory();
        virtual ~inventory();

        int incItem(std::string);
        int addItem(std::string, unsigned int);
        int decItem(std::string);
        int removeItem(std::string, unsigned int);

        void setItemAmount(std::string, unsigned int);
        unsigned int getItemAmount(std::string);

        unsigned int getNumOfItems();

        std::vector<std::string> getNameList(unsigned int);

        const std::map<std::string, inventorySlot>& getInventory() const { return _inventorySlots; };

        const inventorySlot& operator[](std::string);

        int getMoney() const { return _money; };
        void setMoney(int val) { _money = val; };

        void addMoney(int val) { _money += val};
    protected:
    private:
        std::map<std::string, inventorySlot> _inventorySlots;
        inventorySlot null;

        int _money;
};

#endif // INVENTORY_H
