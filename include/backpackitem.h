#ifndef BACKPACKITEM_H
#define BACKPACKITEM_H

#include <string>


class backPackItem
{
    public:
        backPackItem();
        virtual ~backPackItem();
        backPackItem(const backPackItem& other);
        backPackItem& operator=(const backPackItem& other);

        int useInBattle();
        int useOnMap();

        std::string getDescription() { return _description; };
        int getSalePrice() { return _price * 0.7; };
        int gerBuyPrice() { return _price; };

        bool isComsumable() { return _iscomsumable; };

    protected:
    private:
        int use();

        bool _iscomsumable;
        int _price;

        std::string _description;
};

#endif // BACKPACKITEM_H
