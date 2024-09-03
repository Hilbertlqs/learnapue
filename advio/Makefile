ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "linux"
    EXTRALIBS=-lrt
endif
ifeq "$(PLATFORM)" "solaris"
    EXTRALIBS=-lrt
endif

OUTPUT_DIR = $(ROOT)/build/advio
PROGS = deadlock mandatory nonblockw# mcopy2 rot13a
MOREPROGS = rot13c2

all: $(OUTPUT_DIR) $(PROGS) $(OUTPUT_DIR)/lockfile.o# $(MOREPROGS)

rot13c2.c: rot13c2.c.in $(LIBAPUE)
	./fixup.awk rot13a.c >xlate
	sed '/same/q' rot13c2.c.in >rot13c2.c
	cat xlate >>rot13c2.c
	sed '1,/same/d' rot13c2.c.in >>rot13c2.c

%: %.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(OUTPUT_DIR)/$@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/lockfile.o: lockfile.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR):
	if [ ! -d $(ROOT)/build ]; then \
		echo "mkdir $(ROOT)/build"; \
		mkdir $(ROOT)/build; \
		echo "mkdir $@"; \
		mkdir $@; \
	else \
		if [ ! -d $@ ]; then \
			echo "mkdir $@"; \
			mkdir $@; \
		fi \
	fi
	# or
	# if [ ! -d $(ROOT)/build ]; \
	# then \
	# 	echo "mkdir $(ROOT)/build"; \
	# 	mkdir $(ROOT)/build; \
	# 	echo "mkdir $@"; \
	# 	mkdir $@; \
	# else \
	# 	if [ ! -d $@ ]; \
	# 	then \
	# 		echo "mkdir $@"; \
	# 		mkdir $@; \
	# 	fi \
	# fi

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o xlate rot13c2.c

include $(ROOT)/Make.libapue.inc
