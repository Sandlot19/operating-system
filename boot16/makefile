CXX = g++
ASM_FLAGS = -x assembler
CXX_FLAGS = -x c++ -ffreestanding -nostdlib -Wall -Wextra -std=c++11 -I.
LD_FLAGS = -Tscript.ld -ffreestanding -nostdlib -z max-page-size=0x1000 -Wl,--build-id=none -static
SRC_ASM = $(wildcard *.S)
OBJS := $(patsubst %.S,objs/%.o, $(SRC_ASM))
OUT = boot.bin
ELF = boot.elf
OBJCOPY = objcopy
MKDIR = mkdir -p
DIRS = objs

all: $(DIRS) $(OUT)

$(DIRS):
	@$(MKDIR) $@

$(OUT): $(OBJS)
	$(CXX) $(LD_FLAGS) -o $(ELF) $(OBJS)
	$(OBJCOPY) -O binary $(ELF) $(OUT)

$(OBJS): $(SRC_ASM)
	$(CXX) $(ASM_FLAGS) -o $@ -c $<

.PHONY: all clean
clean:
	rm -rf $(DIRS) $(ELF) $(OUT)
