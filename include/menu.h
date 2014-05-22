#ifndef MENU_H
#define MENU_H


class Menu
{
    public:
        void showMainMenu();
        void showInvMenu();
        void showTeamMenu();
    protected:
    private:
        unsigned int cursorPos = 0;
};

#endif // MENU_H
