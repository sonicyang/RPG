#ifndef SKILLMENU_H
#define SKILLMENU_H

#include <menu.h>


class SkillMenu : public Menu
{
    public:
        SkillMenu(std::deque< std::vector< variant<paraVarType> > >&, std::map< std::string, variant<paraVarType> >&);
        virtual ~SkillMenu();

        virtual int processInput(int);

        void init(int val, int m);
    protected:
    private:
        unsigned int currentPos;
        unsigned int _limiter;
        unsigned int mode;
};

#endif // SKILLMENU_H
