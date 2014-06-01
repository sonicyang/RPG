#ifndef VENDER_H
#define VENDER_H

#include <vector>
#include <string>

#include "inventory.h"
#include "genericcontorller.h"
#include "render.h"

class Engine;

class Vender : public genericContorller
{
    public:
        Vender(Engine*, std::map< std::string, variant<paraVarType> >&);
        virtual ~Vender();

        int setUp(std::vector<std::string>);

        int hKeyUp();
        int hKeyDown();
        int hKeyZ();
        int hKeyX();

        int hRender(render&);

        inventory& getVenderInv(){ return venderInv; };

        std::vector<std::string>& getOptions() { return mOptions; };

    protected:
    private:
        std::map< std::string, variant<paraVarType> >& varMap;

        std::vector<std::string> mOptions;

        inventory venderInv;

        unsigned int topCurPos = 0;
};

#endif // VENDER_H
