#ifndef SKILL_H
#define SKILL_H

#include <string>

class Skill
{
    public:
        Skill();
        Skill(std::string path);
        virtual ~Skill();

        std::string getName() { return _name; };
        std::string getDescription() { return _description; };
    protected:
    private:
        std::string _name = "Null";
        std::string _description = "Null";
        int _MPC = 0;
        int _eTarget = -1;
        int _eHPv = 0;
        int _eMPv = 0;
        int _eATKv = 0;
        int _eDEFv = 0;
        int _fTarget = -1;
        int _fHPv = 0;
        int _fMPv = 0;
        int _fATKv = 0;
        int _fDEFv = 0;
};

#endif // SKILL_H
