#ifndef SKILLMENU_H
#define SKILLMENU_H

#include <menu.h>

class Engine;

class SkillMenu : public Menu
{
    public:
        SkillMenu(Engine*, std::map< std::string, variant<paraVarType> >&);
        virtual ~SkillMenu();


        void init(int val, int m);
    protected:
    private:
        unsigned int currentPos;
        unsigned int _limiter;
        unsigned int mode;
};

#endif // SKILLMENU_H
