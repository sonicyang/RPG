#ifndef SKILLMENU_H
#define SKILLMENU_H

#include "menu.h"
#include "character.h"

class Engine;

class SkillMenu : public Menu
{
    public:
        SkillMenu(Engine*, std::map< std::string, variant<paraVarType> >&);
        virtual ~SkillMenu();
        
        int hKeyUp();
        int hKeyDown();
        int hKeyZ();
        int hKeyX();
        int hKeyQ();

        int hRender();

        void init(int m, Character* c);
    protected:
    private:
        unsigned int currentPos;
        unsigned int _limiter;
        unsigned int mode;
        Character* currChara;
};

#endif // SKILLMENU_H
