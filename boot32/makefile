CXX = gcc
ASM_FLAGS = -x assembler -m32
CXX_FLAGS = -x c -ffreestanding -nostdlib -Wall -Wextra -I. -fno-stack-protector -MD -MP -O2 -m32
LD_FLAGS = -Tscript.ld -ffreestanding -nostdlib -z max-page-size=0x1000 -Wl,--build-id=none -static -fno-stack-protector -m32
SRC_C = $(wildcard *.c)
SRC_ASM = $(wildcard *.S)
ASM_OBJS = $(patsubst %.S,objs/%.o, $(SRC_ASM))
C_OBJS = $(patsubst %.c,objs/%.o, $(SRC_C))
OBJS := $(ASM_OBJS)
OBJS += $(C_OBJS)
DEPS := $(patsubst %.c,deps/%.d,$(SRC_C))
OUT = boot32.bin
ELF = boot32.elf
OBJCOPY = objcopy
MKDIR = mkdir -p
DIRS = objs deps

all: $(DIRS) $(OUT)

$(DIRS):
	@$(MKDIR) $@

$(OUT): $(ELF)
	$(OBJCOPY) -O binary $(ELF) $(OUT)

$(ELF): $(ASM_OBJS) $(C_OBJS)
	$(CXX) $(LD_FLAGS) -o $(ELF) $(ASM_OBJS) $(C_OBJS)

objs/%.o: %.c deps/%.d
	$(CXX) $(CXX_FLAGS) -MF $(patsubst %.o,deps/%.d,$(@F)) -o $@ -c $<

objs/%.o: %.S
	$(CXX) $(ASM_FLAGS) -o $@ -c $<

deps/%.d: ;
.PRECIOUS: deps/%.d

include $(DEPS)

clean:
	rm -rf $(DIRS) $(ELF) $(OUT)

.PHONY: all clean
