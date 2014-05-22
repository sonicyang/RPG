#include <cstdlib>
#include "team.h"
#include "json/value.h"
#include "json/reader.h"
#include "utils.h"

Team::Team(std::string teamList) : roleCache("data/roles/role_list.lst")
{
    std::string in = get_file_contents(teamList.c_str());

	Json::Value root;
	Json::Reader reader;
	if (reader.parse( in, root )){
	    _cacheCount = root.get("Count", 0 ).asInt();
	    for(unsigned int i = 0; i < _cacheCount; i++){
            Character chara(root["All"][i]["Level"].asInt(), roleCache[root["All"][i]["Role"].asString()]);
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
