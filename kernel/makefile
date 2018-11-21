CC := g++
ASM_SRC := $(wildcard *.S)
CXX_SRC := $(wildcard *.cc)
ASM_OBJ:= $(patsubst %.S,objs/%.o,$(ASM_SRC))
CXX_OBJ := $(patsubst %.cc,objs/%.o,$(CXX_SRC))
OBJS_ALL := $(ASM_OBJ)
OBJS_ALL += $(CXX_OBJ)
OBJS_ALL += $(C_OBJ)
DEPS := $(patsubst %.cc,deps/%.d,$(CXX_SRC))
OUT = kernel.bin
ELF = kernel.elf
OBJCOPY = objcopy
DIRS := objs deps
MKDIR := mkdir -p

-include FLAGS.gnu $(DEPS)

all: $(DIRS) $(OUT)

$(DIRS):
	@$(MKDIR) $@

$(DEPS_ALL): $(ASM_SRC) $(CXX_SRC)

$(OUT): $(ELF)
	$(OBJCOPY) -O binary $(ELF) $(OUT)

$(ELF): $(OBJS_ALL)
	$(CC) $(LDFLAGS) -o $(ELF) $(OBJS_ALL)

$(ASM_OBJ): $(ASM_SRC)
	$(CC) -o $@ -c $(ASMFLAGS) $<

$(CXX_OBJ): $(CXX_SRC)
	$(CC) -o $@ -c $(CXXFLAGS) -MF $(DEPS) $<

clean:
	@rm -rf $(ELF) $(OUT) $(DIRS)

.PHONY: all clean dirs
