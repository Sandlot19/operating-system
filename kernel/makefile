CC := g++
ASM_SRC := $(wildcard *.S)
CXX_SRC := $(wildcard *.cc)
ASM_OBJ := $(patsubst %.S,objs/%.o,$(ASM_SRC))
CXX_OBJ := $(patsubst %.cc,objs/%.o,$(CXX_SRC))
OBJS_ALL := $(ASM_OBJ)
OBJS_ALL += $(CXX_OBJ)
#OBJS_ALL += $(C_OBJ)
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

$(OUT): $(OBJS_ALL)
	$(CC) $(LDFLAGS) -o $(ELF) $(OBJS_ALL)
	$(OBJCOPY) -O binary $(ELF) $(OUT)

objs/%.o: %.cc
	$(CC) -o $@ -c $(CXXFLAGS) -MF $(patsubst %.cc,deps/%.d,$<) $<

objs/%.o: %.S
	$(CC) -o $@ -c $(ASMFLAGS) $<

clean:
	@rm -rf $(ELF) $(OUT) $(DIRS)

.PHONY: all clean dirs
