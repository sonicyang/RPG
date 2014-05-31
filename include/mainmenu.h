#ifndef MAINMENU_H
#define MAINMENU_H

#include <menu.h>

class Engine;

class MainMenu : public Menu
{
    public:
        MainMenu(Engine*, std::map< std::string, variant<paraVarType> >&);
        virtual ~MainMenu();

        int hKeyUp();
        int hKeyDown();
        int hKeyZ();
        int hKeyX();
        int hKeyQ();

        int hRender();

        void init(void);

        std::vector<std::string> getOptions() { return mOption; };
    protected:
    private:
        std::vector<std::string> mOption;

        unsigned int currentPos;
};

#endif // MAINMENU_H
