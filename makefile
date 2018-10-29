TOPTARGETS = all clean
DIRS:=$(filter-out $(wildcard checkpoint*/.), $(wildcard */.))

$(TOPTARGETS): $(DIRS)

$(DIRS):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

clean:
	rm -rf hdd_writer

.PHONY: $(TOPTARGETS) $(DIRS)
