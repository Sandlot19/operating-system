TOPTARGETS = all clean
DIRS=$(wildcard */.)

$(TOPTARGETS): $(DIRS)

$(DIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

clean:
	rm -rf hdd.hdd hdd_writer 

.PHONY: $(TOPTARGETS) $(DIRS)
