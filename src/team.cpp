#include <cstdlib>
#include "team.h"
#include "json/value.h"
#include "json/reader.h"
#include "utils.h"

Team::Team(std::string teamList) : roleCache("data/roles/role_list.lst"), null()
{
    std::string in = get_file_contents(teamList.c_str());

	Json::Value root;
	Json::Reader reader;
	if (reader.parse( in, root )){
	    _cacheCount = root.get("Count", 0 ).asInt();
	    for(unsigned int i = 0; i < _cacheCount; i++){
            Character chara(&roleCache, root["All"][i]["Name"].asString(), root["All"][i]["Level"].asInt(), roleCache[root["All"][i]["Role"].asString()]);
            _cache.insert(_cache.begin(), std::pair<std::string, Character>(root["All"][i]["Name"].asString(), chara));
	    }

        for(unsigned int i = 0; i < root["Default"].size(); i++){
            _team.insert(_team.begin(), std::pair<std::string, Character>(root["Default"][i].asString(), _cache[root["Default"][i].asString()]));
	    }


	}else{
	    std::cout << "Failed to parse configuration\n"  << reader.getFormatedErrorMessages();
	    exit(128);
	}
}

Team::~Team()
{
    //dtor
}

std::vector<std::string> Team::getNameList() const{
    std::vector<std::string> tmp;

    for (auto it = _team.cbegin(); it != _team.cend(); it++){
        tmp.push_back((*it).first);
    }
    return tmp;
}

Character& Team::operator[](std::string subscript){
    if(_team.find(subscript) != _team.end())
        return _team[subscript];
    return null;
}

void Team::addCharToTeam(std::string name){
    if(_cache.find(name) == _cache.end())
        return;
    _team.insert(_team.begin(), std::pair<std::string, Character>(name, _cache[name]));
    return;
}

void Team::removeCharFromTeam(std::string name){
    if(_team.find(name) == _team.end())
        return;
    _team.erase(name);
    return;
}

bool Team::isWipeOut(){
    bool flag = true;
    for (auto it = _team.begin(); it != _team.end(); it++){
        flag &= it->second.isDead();
    }
    return flag;
}
