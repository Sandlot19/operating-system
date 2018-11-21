CXX=g++
CFLAGS=-std=c++17 -MD -MP
SRC=$(filter-out main.cpp,$(wildcard *.cpp))
OBJ=$(patsubst %.cpp,obj/%.o,$(SRC))
DEP=$(patsubst %.cpp,dep/%.d,$(SRC))
DIRS=obj dep
OUT=hdd_writer

-include $(DEP)

.PHONY: all clean

all: $(DIRS) $(OUT)

$(DIRS):
	@mkdir $@

$(OUT): $(OBJ) main.cpp
	$(CXX) -o $(OUT) $(OBJ) main.cpp
	@cp $(OUT) ..

$(OBJ): $(SRC)
	$(CXX) $(CFLAGS) -MF $(DEP) -o $@ -c $<

clean:
	rm -rf $(DIRS) $(OUT)
