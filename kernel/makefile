TOPTARGETS = all
export OBJDIR=objs
export DEPDIR=deps
export INCDIR=$(realpath include)
DIRS=${OBJDIR} ${DEPDIR} include
MODULE_DIRS=$(filter-out $(foreach DIR, ${DIRS}, $(addsuffix /., ${DIR})), $(wildcard */.))

BIN=kernel.bin
ELF=kernel.elf

-include FLAGS.gnu

.PHONY: ${TOPTARGETS} ${DIRS} ${MODULE_DIRS}
${TOPTARGETS}: ${DIRS} ${MODULE_DIRS} ${BIN}
	objcopy -O binary ${ELF} ${BIN}

${BIN}:
	${CXX} ${LDFLAGS} -o ${ELF} $(wildcard ${OBJDIR}/*.o)

${DIRS}:
	$(foreach DIR, $@, $(shell mkdir -p ${DIR}))

${MODULE_DIRS}:
	${MAKE} -C $@ ${MAKECMDGOALS}

clean:
	rm -rf ${OBJDIR} ${DEPDIR} ${BIN} ${ELF}

include ${DEPS}
