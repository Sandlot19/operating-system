SRC:=$(wildcard *.cc)
INCDIR:=$(addprefix ../,${INCDIR})
OBJDIR:=$(addprefix ../,${OBJDIR})
OBJ=$(patsubst %.cc,%.o,${SRC})
OBJ:=$(addprefix ${OBJDIR}/,${OBJ})
DEPDIR:=$(addprefix ../,${DEPDIR})
DEP=$(patsubst %.cc,%.d,${SRC})
DEP:=$(addprefix ${DEPDIR}/,${DEP})

all: ${OBJ}

${OBJDIR}/%.o: %.cc ${DEPDIR}/%.d
	${CXX} -I. ${CXXFLAGS} -MF $(patsubst %.o,${DEPDIR}/%.d,$(@F)) -c -o $@ $<

${DEPDIR}/%.d: ;
.PRECIOUS: ${DEPDIR}/%.d

include $(${SRC}.cc=.o)
