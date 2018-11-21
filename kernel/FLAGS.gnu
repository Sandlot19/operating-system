DEPENDFLAGS   := -MD -MP
INCLUDES      := -I.
BASEFLAGS     := -pedantic -pedantic-errors
BASEFLAGS     := -nostartfiles -ffreestanding
BASEFLAGS     := -static -fno-stack-protector -fno-zero-initialized-in-bss
OPTIFLAGS     := -O2
WARNFLAGS     := -Wall -Wextra -Wshadow -Wcast-align -Wwrite-strings
WARNFLAGS     += -Wredundant-decls -Winline
WARNFLAGS     += -Wformat=2 -Winit-self
WARNFLAGS     += -Winvalid-pch -Wmissing-format-attribute
WARNFLAGS     += -Wmissing-include-dirs -Wno-multichar
WARNFLAGS     += -Wswitch -Wundef
WARNFLAGS     += -Wdisabled-optimization -Wpointer-arith
WARNFLAGS     += -Werror
LDFLAGS       := -Tscript.ld -Wl,--build-id=none -nostdlib -nostartfiles -zmax-page-size=0x1000 $(EXTRA_LDFLAGS)
ASMFLAGS      := -x assembler $(INCLUDES) $(DEPENDFLAGS) $(BASEFLAGS) $(WARNFLAGS) $(OPTIFLAGS)
CFLAGS        := -x c $(INCLUDES) $(DEPENDFLAGS) $(BASEFLAGS) $(WARNFLAGS) $(OPTIFLAGS)
CFLAGS        += -std=gnu99
CFLAGS        += $(EXTRA_CFLAGS)
CXXFLAGS      := -x c++ $(INCLUDES) $(DEPENDFLAGS) $(BASEFLAGS) $(WARNFLAGS) $(OPTIFLAGS)
CXXFLAGS      += -std=c++17 -fno-exceptions -fno-threadsafe-statics -fno-rtti
CXXFLAGS      += $(EXTRA_CXXFLAGS)
