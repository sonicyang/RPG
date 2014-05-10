#ifndef PLAYER_H
#define PLAYER_H


class player
{
    public:
        player();
        ~player();
        Point GetCord() { return m_Cord; }
        void SetCord(Point val) { m_Cord = val; }
        char Geticon() { return m_icon; }
        void Seticon(char val) { m_icon = val; }
    protected:
    private:
        Point m_Cord;
        char m_icon;
};

#endif // PLAYER_H
