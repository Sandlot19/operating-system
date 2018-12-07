SRC:=$(wildcard *.S)
OBJDIR:=$(addprefix ../, ${OBJDIR})
OBJ=$(patsubst %.S,%.o,${SRC})
OBJ:=$(addprefix ${OBJDIR}/, ${OBJ})

all: ${OBJ}

${OBJDIR}/%.o: %.S
	${CXX} ${OPTIFLAGS} ${WARNFLAGS} ${ASMFLAGS} -c -o $@ $<
