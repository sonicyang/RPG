CXX = g++
CXXFLAG = -Wall -std=c++11 -g

PWD = .

GAMESRC = $(PWD)/src
JSONSRC = $(PWD)/src/lib_json

# Include flags
INCLUDE = -I $(PWD)/include
INCLUDE += $(shell pkg-config --cflags ncurses)

# Libs flags
LIB += $(shell pkg-config --libs ncurses)
LIB += -lcurses

OBJDIR = $(PWD)/obj/

OBJ += main.o chararray2d.o controller.o eventcontroller.o gmap.o mapcontroller.o mapobject.o objplayer.o point.o prompt.o render.o utils.o
OBJ += json_reader.o json_value.o json_writer.o


OUT_EXE = RPG

# Game parts
$(OUT_EXE): $(OBJ)
	@echo "    LD    "$@
	@$(CXX) $(OBJDIR)/*.o $(CXXFLAG) $(LIB) -o $@

Debug:  $(OBJ)
	@echo " LD-DEBUG  "$@
	@$(CXX) $(OBJDIR)/$(OBJ) $(CXXFLAG) $(LIB) -o $@
	
%.o: $(GAMESRC)/%.cpp
	@echo "    CC    "$@
	@$(CXX) $< $(CXXFLAG) $(INCLUDE) -c -o $(OBJDIR)/$*.o

main.o: $(PWD)/main.cpp
	@echo "    CC    "$@
	@$(CXX) $< $(CXXFLAG) $(INCLUDE) -c -o $(OBJDIR)/$*.o

#Json parts
%.o: $(JSONSRC)/%.cpp
	@echo "    CC    "$@
	@$(CXX) $< $(CXXFLAG) $(INCLUDE) -c -o $(OBJDIR)/$*.o


.PHONY: clean
clean:
	rm -frv $(OUT_EXE)
	rm -frv $(OBJDIR)/*.o
