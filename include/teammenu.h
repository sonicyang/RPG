#ifndef TEAMMENU_H
#define TEAMMENU_H

#include <menu.h>


class TeamMenu : public Menu
{
    public:
        TeamMenu(std::deque< std::vector< variant<paraVarType> > >&, std::map< std::string, variant<paraVarType> >&);
        virtual ~TeamMenu();

        virtual int processInput(int);

        void init(int val, int m);
    protected:
    private:
        unsigned int currentPos;
        unsigned int _limiter;
        unsigned int mode;
};

#endif // TEAMMENU_H
