#ifndef BACKPACKITEM_H
#define BACKPACKITEM_H

#include <string>


class Item
{
    public:
        Item(std::string, std::string, int, bool);
        virtual ~Item();
        Item(const Item& other);
        Item& operator=(const Item& other);

        int useInBattle();
        int useOnMap();

        std::string getName() { return _name; };
        std::string getDescription() { return _description; };
        int getSalePrice() { return _price * 0.7; };
        int gerBuyPrice() { return _price; };

        bool isComsumable() { return _iscomsumable; };

    protected:
    private:
        int use();

        std::string _name;
        std::string _description;
        int _price;
        bool _iscomsumable;
};

#endif // BACKPACKITEM_H
