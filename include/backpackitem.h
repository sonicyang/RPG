#ifndef BACKPACKITEM_H
#define BACKPACKITEM_H


class backPackItem
{
    public:
        backPackItem();
        virtual ~backPackItem();
        backPackItem(const backPackItem& other);
        backPackItem& operator=(const backPackItem& other);
    protected:
    private:
};

#endif // BACKPACKITEM_H
