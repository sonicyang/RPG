#include "controller.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include "gmap.h"
#include "point.h"
#include "utils.h"
#include "json/reader.h"
#include "json/value.h"
#include <string>
#include <curses.h>
#include "render.h"

Controller::Controller(char* maplist) : rdr()
{
    std::string in = get_file_contents(maplist);

    Json::Value root;
    Json::Reader reader;
    bool stat = reader.parse( in, root );
    if (stat){
        map_count = root.get("Count", 0 ).asInt();
        for(int i = 0; i < map_count; i++){
            gmap tmp(root["Path"][i].asString().c_str());
            map_list.insert (map_list.begin(), std::pair<std::string,gmap>(tmp.Getname(),tmp));
        }
        default_map = current_map = root["Default"].asString();

    }else{
        std::cout << "Failed to parse configuration\n"  << reader.getFormatedErrorMessages();
    }

    cbreak();
    noecho();
    keypad(stdscr, TRUE);

}

Controller::~Controller()
{
}

gmap Controller::get_CurrentMap(){
    return map_list[current_map];
}

void Controller::updateScreen(){
    rdr.render_map(map_list[current_map]);
    rdr.render_map_object(map_list[current_map].getPlayer());
    rdr.update();
    return;
}
void Controller::waitUserCommand(){
    int c = getch();
    switch (c) {
        case KEY_LEFT:
            map_list[current_map].movePlayer(Point(-1,0));
            break;
        case KEY_RIGHT:
            map_list[current_map].movePlayer(Point(1,0));
            break;
        case KEY_UP:
            map_list[current_map].movePlayer(Point(0,-1));
            break;
        case KEY_DOWN:
            map_list[current_map].movePlayer(Point(0,1));
            break;
        case KEY_END:
            exit(1);
    }
    return;
}
