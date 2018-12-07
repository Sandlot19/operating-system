export DEPENDFLAGS   := -MD -MP
export INCLUDES      := -I${INCDIR}
export BASEFLAGS     := -pedantic -pedantic-errors
export BASEFLAGS     := -nostartfiles -ffreestanding
export BASEFLAGS     := -static -fno-stack-protector -fno-zero-initialized-in-bss
export OPTIFLAGS     := -O2
export WARNFLAGS     := -Wall -Wextra -Wshadow -Wcast-align -Wwrite-strings
export WARNFLAGS     += -Wredundant-decls -Winline
export WARNFLAGS     += -Wformat=2 -Winit-self
export WARNFLAGS     += -Winvalid-pch -Wmissing-format-attribute
export WARNFLAGS     += -Wmissing-include-dirs -Wno-multichar
export WARNFLAGS     += -Wswitch -Wundef
export WARNFLAGS     += -Wdisabled-optimization -Wpointer-arith
export WARNFLAGS     += -Werror
export LDFLAGS       := -Tscript.ld -Wl,--build-id=none -nostdlib -nostartfiles -zmax-page-size=0x1000 $(EXTRA_LDFLAGS)
export ASMFLAGS      := -x assembler $(INCLUDES) $(DEPENDFLAGS) $(BASEFLAGS) $(WARNFLAGS) $(OPTIFLAGS)
export CFLAGS        := -x c $(INCLUDES) $(DEPENDFLAGS) $(BASEFLAGS) $(WARNFLAGS) $(OPTIFLAGS)
export CFLAGS        += -std=gnu99
export CFLAGS        += $(EXTRA_CFLAGS)
export CXXFLAGS      := -x c++ $(INCLUDES) $(DEPENDFLAGS) $(BASEFLAGS) $(WARNFLAGS) $(OPTIFLAGS)
export CXXFLAGS      += -std=c++17 -fno-exceptions -fno-threadsafe-statics -fno-rtti
export CXXFLAGS      += $(EXTRA_CXXFLAGS)
