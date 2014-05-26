#include "itemexec.h"

#include "menu.h"
#include "render.h"
#include "prompt.h"

int ItemExec::Exec(inventory& inv, int item, Team& team, int chara, render& rdr){

    std::string name = inv.getNameList(item)[0];

        switch(inv[name].item.getType()){
            case itemTypes::potion:{
                team[team.getNameList()[chara]].varHP(inv[name].item.getHPVarient());
                team[team.getNameList()[chara]].varMP(inv[name].item.getMPVarient());

                break;
            }
            case itemTypes::allPotion:{
                    std::vector<std::string> memberList = team.getNameList();
                    for(unsigned int i = 0; i < memberList.size(); i++){
                        team[team.getNameList()[i]].varHP(inv[name].item.getHPVarient());
                        team[team.getNameList()[i]].varMP(inv[name].item.getMPVarient());
                    }
                    break;
            }
        }

        if(inv[name].item.isComsumable())
            inv.decItem(name);
    return 0;
}

int ItemExec::changeItem(inventory& inv, int item, Team& team, int chara, int slot, render& rdr){
    Item selectedItem = inv[inv.getNameList(item)[0]].item;
    Item currItemName;

    int ret;
    std::string cname = team.getNameList()[chara];

    switch(slot){
        case 0:
            currItemName = team[cname].getHead();
            ret = team[cname].setHead(selectedItem);
            break;
        case 1:
            currItemName = team[cname].getArmor();
            ret = team[cname].setArmor(selectedItem);
            break;
        case 2:
            currItemName = team[cname].getLegs();
            ret = team[cname].setLegs(selectedItem);
            break;
        case 3:
            currItemName = team[cname].getShoes();
            ret = team[cname].setShoes(selectedItem);
            break;
        case 4:
            currItemName = team[cname].getWeapon();
            ret = team[cname].setWeapon(selectedItem);
            break;
        }

    if(ret == -1){
        rdr.render_prompt(prompt(L"You can't wear a shoe on your Head", L"System"));
        while(getch()!='z');
    }else{
        inv.decItem(inv.getNameList(item)[0]);
        if(currItemName.getName() != "Empty")
            inv.incItem(currItemName.getName());
    }

    return 0;
}
