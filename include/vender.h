#ifndef VENDER_H
#define VENDER_H

#include <vector>
#include <string>

#include "inventory.h"

class Vender
{
    public:
        Vender(std::deque< std::vector< variant<paraVarType> > >&, std::map< std::string, variant<paraVarType> >&);
        virtual ~Vender();

        int setUp(std::vector<std::string>);

        int processInput(int c);

        inventory& getVenderInv(){ return venderInv; };

        int getProcessStat() { return processStat; };
        std::vector<std::string>& getOptions() { return mOptions; };

    protected:
    private:
        std::deque< std::vector< variant<paraVarType> > >& ctlCallStack;
        std::map< std::string, variant<paraVarType> >& varMap;

        std::vector<std::string> mOptions;

        inventory venderInv;
        int processStat = 0;

        unsigned int topCurPos = 0;
        unsigned int venderInvCurPos = 0;
};

#endif // VENDER_H
