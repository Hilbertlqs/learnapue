DIRS = lib intro advio daemons datafiles environ fileio filedir proc relation signals standards stdio threadctl threads

all:
	for i in $(DIRS); do \
		(cd $$i && echo "making $$i" && $(MAKE)) || exit 1; \
	done

clean:
	for i in $(DIRS); do \
		(cd $$i && echo "cleaning $$i" && $(MAKE) clean) || exit 1; \
	done
	rm -rf build
