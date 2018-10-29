CXX = g++
ASM_FLAGS = -x assembler
CXX_FLAGS = -x c++ -ffreestanding -nostdlib -Wall -Wextra -std=c++11 -I.
LD_FLAGS = -Tscript.ld -ffreestanding -nostdlib -z max-page-size=0x1000 -Wl,--build-id=none -static
SRC_CPP = $(wildcard *.cc)
SRC_ASM = $(wildcard *.S)
OBJS := $(patsubst %.S,objs/%.o, $(SRC_ASM))
OBJS += $(patsubst %.cc,objs/%.o, $(SRC_CPP))
DEPS = $(patsubst %.cpp,deps/%.d, $(SRC_CPP))
OUT = boot.bin
ELF = boot.elf
OBJCOPY = objcopy
MKDIR = mkdir -p
DIRS = objs deps

all: $(DIRS) $(OUT)

include $(wildcard deps/*.d)

$(DIRS):
	@$(MKDIR) $@

$(OUT): $(OBJS) makefile script.ld
	$(CXX) $(LD_FLAGS) -o $(ELF) $(OBJS)
	$(OBJCOPY) -O binary $(ELF) $(OUT)

objs/%.o: %.cc makefile script.ld
	$(CXX) $(CXX_FLAGS) -o $@ -c $<

objs/%.o: %.S makefile script.ld
	$(CXX) $(ASM_FLAGS) -o $@ -c $<

.PHONY: all clean
clean:
	rm -rf $(DIRS) $(ELF) $(OUT)
