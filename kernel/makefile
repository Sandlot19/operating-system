TOPTARGETS = all
export OBJDIR=objs
export DEPDIR=deps
export INCDIR=$(realpath include)
DIRS=${OBJDIR} ${DEPDIR} include
MODULE_DIRS=$(filter-out $(foreach DIR, ${DIRS}, $(addsuffix /., ${DIR})), $(wildcard */.))

EXT=cc S
ALLSRC:=$(shell echo $(EXT) | xargs -n 1 echo | sed 's,^, -or -name *.,' | xargs find . -name {})
SRC:=$(notdir $(ALLSRC))
OBJ=$(patsubst %.cc,$(OBJDIR)/%.o,$(filter %.cc,$(SRC)))
OBJ+=$(patsubst %.S,$(OBJDIR)/%.o,$(filter %.S,$(SRC)))
BIN=kernel.bin
ELF=kernel.elf

-include FLAGS.gnu

.PHONY: ${TOPTARGETS} ${DIRS} ${MODULE_DIRS}
${TOPTARGETS}: ${DIRS} ${MODULE_DIRS} ${BIN}

${BIN}: ${ELF}
	objcopy -O binary ${ELF} ${BIN}

$(ELF): $(OBJ)
	${CXX} ${LDFLAGS} -o ${ELF} $(wildcard ${OBJDIR}/*.o)

${DIRS}:
	$(foreach DIR, $@, $(shell mkdir -p ${DIR}))

${MODULE_DIRS}:
	${MAKE} -C $@ ${MAKECMDGOALS}

clean:
	rm -rf ${OBJDIR} ${DEPDIR} ${BIN} ${ELF}
