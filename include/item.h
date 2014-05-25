#ifndef BACKPACKITEM_H
#define BACKPACKITEM_H

#include <string>


class Item
{
    public:
        Item();
        Item(std::string);
        virtual ~Item();
        Item(const Item& other);
        Item& operator=(const Item& other);

        int useInBattle();
        int useOnMap();

        unsigned int getID() const { return _id; };
        std::string getName() const { return _name; };
        std::string getDescription() const { return _description; };
        int getSalePrice() const { return _price * 0.7; };
        int gerBuyPrice() const { return _price; };

        bool isComsumable() { return _iscomsumable; };

        int getHPVarient() { return _HPv; };
        int getMPVarient() { return _MPv; };
        int getATKVarient() { return _ATKv; };
        int getDEFVarient() { return _DEFv; };


        bool operator<(const Item&) const;
        bool operator<=(const Item&) const;
        bool operator>(const Item&) const;
        bool operator>=(const Item&) const;
        bool operator==(const Item&) const;
        bool operator!=(const Item&) const;

    protected:
    private:
        int use();

        unsigned int _id = 0xffffffff;
        std::string _name = "NULL";
        std::string _description = "NULL ITEM";
        int _price = 0;
        bool _iscomsumable = 0;

        int _type = -1;

        int _HPv = 0;
        int _MPv = 0;
        int _ATKv = 0;
        int _DEFv = 0;
};

#endif // BACKPACKITEM_H
