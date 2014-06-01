#ifndef STARTMENU_H
#define STARTMENU_H

#include "menu.h"
#include "render.h"

class Engine;

class StartMenu : public Menu
{
    public:
        StartMenu(Engine*, std::map< std::string, variant<paraVarType> >&);
        virtual ~StartMenu();

        int hKeyUp();
        int hKeyDown();
        int hKeyZ();

        int hRender(render&);
        
        void init();

        std::vector<std::string> getOptions() { return mOption; };
    protected:
    private:
        std::vector<std::string> mOption;

        unsigned int currentPos;
};

#endif // STARTMENU_H
