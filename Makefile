CXX = g++
CXXFLAG = -Wall -std=c++11 -g

PWD = .

GAMESRC = $(PWD)/src
JSONSRC = $(PWD)/src/lib_json

# Include flags
INCLUDE = -I $(PWD)/include
INCLUDE += $(shell pkg-config --cflags ncursesw)

# Libs flags
LIB += $(shell pkg-config --libs ncursesw)
LIB += -lcurses

OBJDIR = $(PWD)/obj/

OBJ = main.o array2d.o engine.o inventory.o item.o eventcontroller.o gmap.o mapcontroller.o mapobject.o objplayer.o point.o prompt.o render.o utils.o utf8.o battle.o character.o charmenu.o invmenu.o itemexec.o mainmenu.o menu.o monster.o monsterfactory.o  role.o rolefactory.o skill.o skillmenu.o team.o teammenu.o genericcontorller.o vender.o
OBJ += json_reader.o json_value.o json_writer.o


OUT_EXE = RPG

# Game parts
$(OUT_EXE): $(addprefix $(OBJDIR),$(OBJ))
	@echo "    LD    "$@
	@$(CXX) $(addprefix $(OBJDIR),$(OBJ)) $(CXXFLAG) $(LIB) -o $@

debug:  $(OBJ)
	@echo " LD-DEBUG  "$@
	@$(CXX) $(OBJDIR)/$(OBJ) $(CXXFLAG) $(LIB) -o $@

$(OBJDIR)%.o: $(GAMESRC)/%.cpp
	@echo "    CC    "$@
	@$(CXX) $< $(CXXFLAG) $(INCLUDE) -c -o $@

$(OBJDIR)main.o: $(PWD)/main.cpp
	@echo "    CC    "$@
	@$(CXX) $< $(CXXFLAG) $(INCLUDE) -c -o $@

#Json parts
$(OBJDIR)%.o: $(JSONSRC)/%.cpp
	@echo "    CC    "$@
	@$(CXX) $< $(CXXFLAG) $(INCLUDE) -c -o $@


.PHONY: clean
clean:
	rm -frv $(OUT_EXE)
	rm -frv $(OBJDIR)/*.o
