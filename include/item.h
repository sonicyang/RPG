#ifndef BACKPACKITEM_H
#define BACKPACKITEM_H

#include <string>


class Item
{
    public:
        Item();
        Item(std::string);
        virtual ~Item();
        //Item(const Item& other);
        //Item& operator=(const Item& other);

        unsigned int getID() const { return _id; };
        std::string getName() const { return _name; };
        std::string getDescription() const { return _description; };
        int getSalePrice() const { return _price * 0.7; };
        int gerBuyPrice() const { return _price; };

        bool isComsumable() const { return _iscomsumable; };
        bool isUsable() const;

        int getHPVarient() const { return _HPv; };
        int getMPVarient() const { return _MPv; };
        int getATKVarient() const { return _ATKv; };
        int getDEFVarient() const { return _DEFv; };

        int getType() const { return _type; };

        bool operator<(const Item&) const;
        bool operator<=(const Item&) const;
        bool operator>(const Item&) const;
        bool operator>=(const Item&) const;
        bool operator==(const Item&) const;
        bool operator!=(const Item&) const;

    protected:
    private:

        unsigned int _id = 0xffffffff;
        std::string _name = "";
        std::string _description = "";
        int _price = 0;
        bool _iscomsumable = 0;

        int _type = -1;

        int _HPv = 0;
        int _MPv = 0;
        int _ATKv = 0;
        int _DEFv = 0;
};

#endif // BACKPACKITEM_H
