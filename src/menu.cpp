#include "menu.h"

Menu::Menu(std::deque< std::vector< variant<paraVarType> > >& a, std::map< std::string, variant<paraVarType> >& b) :
    ctlCallStack(a),
    varMap(b)
{

}

Menu::~Menu()
{
}

