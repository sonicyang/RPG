#ifndef HELPMENU_H
#define HELPMENU_H

#include <menu.h>

class Engine;

class HelpMenu : public Menu
{
    public:
        HelpMenu(Engine*, std::map< std::string, variant<paraVarType> >&);
        virtual ~HelpMenu();

        int hKeyZ();
        int hKeyX();

        int hRender();
    
    protected:
    private:
};

#endif // HELPMENU_H
