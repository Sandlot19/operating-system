CXX = gcc
ASM_FLAGS = -x assembler
CXX_FLAGS = -x c++ -ffreestanding -nostdlib -Wall -Wextra -std=c++11 -I.
LD_FLAGS = -Tscript.ld -ffreestanding -nostdlib -z max-page-size=0x1000 -Wl,--build-id=none -static
SRC_C = $(wildcard *.c)
SRC_ASM = $(wildcard *.S)
ASM_OBJS = $(patsubst %.S,objs/%.o, $(SRC_ASM))
C_OBJS = $(patsubst %.c,objs/%.o, $(SRC_C))
OBJS := $(ASM_OBJS)
OBJS += $(C_OBJS)
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

$(C_OBJS): $(SRC_C)
	$(CXX) $(CXX_FLAGS) -o $@ -c $<

$(ASM_OBJS): $(SRC_ASM)
	$(CXX) $(ASM_FLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -rf $(DIRS) $(ELF) $(OUT)
