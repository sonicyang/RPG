#ifndef CHARMENU_H
#define CHARMENU_H

#include <menu.h>


class CharMenu : public Menu
{
    public:
        CharMenu(std::deque< std::vector< variant<paraVarType> > >&, std::map< std::string, variant<paraVarType> >&);
        virtual ~CharMenu();

        virtual int processInput(int);

        void init(int m);
    protected:
    private:
        unsigned int currentPos;
        unsigned int mode;
        bool processPending = 0;
};

#endif // CHARMENU_H
