CXX = g++
CXXFLAG = -Wall -std=c++11 -g

PWD = .

SRC = $(PWD)/src

# Include flags
INCLUDE = -I $(PWD)/include
INCLUDE += $(shell pkg-config --cflags ncurses)
#INCLUDE += $(shell pkg-config --cflags json)
#INCLUDE += -I /usr/include/jsoncpp

# Libs flags
LIB += $(shell pkg-config --libs ncurses)
LIB += -L$(PWD)/lib/ -lpdcurses
#LIB += $(shell pkg-config --libs json)
LIB += -ljsoncpp

OBJ = main.o chararray2d.o controller.o eventcontroller.o gmap.o mapcontroller.o mapobject.o objplayer.o point.o prompt.o render.o utils.o

OUT_EXE = RPG

$(OUT_EXE): $(OBJ)
	@echo "    LD    "$@
	@$(CXX) $(OBJ) $(CXXFLAG) $(LIB) -o $@

Debug:  $(OBJ)
	@echo " LD-DEBUG  "$@
	@$(CXX) $(OBJ) $(CXXFLAG) $(LIB) -o $@
	
%.o: $(SRC)/%.cpp
	@echo "    CC    "$@
	@$(CXX) $< $(CXXFLAG) $(INCLUDE) -c

main.o: $(PWD)/main.cpp
	@echo "    CC    "$@
	@$(CXX) $< $(CXXFLAG) $(INCLUDE) -c

.PHONY: clean
clean:
	rm -frv *.o $(OUT_EXE)
