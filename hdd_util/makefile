CXX=g++
CFLAGS=-std=c++11
SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp,%.o, $(SRC))
OUT=hdd_writer

.PHONY: clean

all: $(OBJ)
	$(CXX) $(CFLAGS) -o $(OUT) $(OBJ)
	mv $(OUT) ..

$(OBJ): $(SRC)
	$(CXX) $(CFLAGS) -c $(SRC)

clean:
	rm -rf $(OBJ) $(OUT)
