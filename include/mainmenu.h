#ifndef MAINMENU_H
#define MAINMENU_H

#include <menu.h>

class MainMenu : public Menu
{
    public:
        MainMenu(std::deque< std::vector< variant<paraVarType> > >&, std::map< std::string, variant<paraVarType> >&);
        virtual ~MainMenu();

        virtual int processInput(int);

        void init(void);

        std::vector<std::string> getOptions() { return mOption; };
    protected:
    private:
        std::vector<std::string> mOption;

        unsigned int currentPos;
};

#endif // MAINMENU_H
