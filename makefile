TOPTARGETS = all clean
DIRS:=$(filter-out $(wildcard checkpoint*/.), $(wildcard */.))
DIRS:=$(filter-out $(wildcard bochs/.), $(DIRS))


$(TOPTARGETS): $(DIRS)

all: hdd

$(DIRS):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

hdd.hdd: ;

hdd: hdd.hdd
	./hdd_writer -o hdd.hdd boot16/boot.bin boot32/boot32.bin kernel/kernel.bin

#TODO: add bochs directive to make bochs from root directory

clean:
	rm -rf hdd_writer hdd.hdd

.PHONY: $(TOPTARGETS) $(DIRS)
