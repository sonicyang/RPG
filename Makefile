CXX = g++
CXXFLAG = -Wall -std=c++11 -g3
DEGUBBER = lldb

PWD = .

GAMESRC = $(PWD)/src
JSONSRC = $(PWD)/src/lib_json

# Include flags
INCLUDE = -I $(PWD)/include
INCLUDE += $(shell pkg-config --cflags ncursesw)

# Libs flags
LIB += $(shell pkg-config --libs ncursesw)
LIB += -lcurses
LIB += -lSDL2

OBJDIR = $(PWD)/obj/

OBJ = main.o engine.o
OBJ += genericcontorller.o mapcontroller.o eventcontroller.o battle.o prompt.o inventory.o vender.o team.o
OBJ += menu.o mainmenu.o startmenu.o helpmenu.o invmenu.o teammenu.o skillmenu.o charmenu.o
OBJ += item.o
OBJ += gmap.o mapobject.o objplayer.o
OBJ += rolefactory.o role.o skill.o 
OBJ += character.o monster.o monsterfactory.o
OBJ += array2d.o point.o utils.o utf8.o
OBJ += render.o itemexec.o
OBJ += json_reader.o json_value.o json_writer.o


OUT_EXE = RPG

# Game parts
$(OUT_EXE): $(addprefix $(OBJDIR),$(OBJ))
	@echo "    LD    "$@
	@$(CXX) $(addprefix $(OBJDIR),$(OBJ)) $(CXXFLAG) $(LIB) -o $@

debug: $(OUT_EXE)
	@echo " START-DEBUG  "$@
	@$(DEBUGGER) $(PWD)/$(OUT_EXE)

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
