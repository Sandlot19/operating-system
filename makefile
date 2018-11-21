TOPTARGETS = all clean
DIRS:=$(filter-out $(wildcard checkpoint*/.), $(wildcard */.))

$(TOPTARGETS): $(DIRS)

$(DIRS):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

hdd:
	./hdd_writer -o hdd.hdd boot16/boot.bin boot32/boot.bin kernel/kernel.bin

clean:
	rm -rf hdd_writer

.PHONY: $(TOPTARGETS) $(DIRS) hdd
