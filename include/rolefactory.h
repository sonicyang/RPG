#ifndef ROLEFACTORY_H
#define ROLEFACTORY_H

#include <string>
#include <map>
#include "role.h"

class RoleFactory
{
    public:
        RoleFactory(std::string roleList);
        virtual ~RoleFactory();

        Role operator[](std::string val) { return _roleCache[val]; };
    protected:
    private:

        unsigned int _roleCount;
        std::map<std::string, Role> _roleCache;
};

#endif // ROLEFACTORY_H