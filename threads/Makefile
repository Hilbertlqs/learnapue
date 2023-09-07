ROOT = ..
EXTRALIBS = -pthread
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

BAR =
ifeq "$(PLATFORM)" "macos"
    TLOCK =
    EXTRALIBS = -pthread
else
    TLOCK = timedlock
endif
ifeq "$(PLATFORM)" "linux"
    BAR = barrier
    EXTRALIBS = -pthread -lrt -lbsd
endif
ifeq "$(PLATFORM)" "freebsd"
    BAR = barrier
    EXTRALIBS = -pthread
endif
ifeq "$(PLATFORM)" "solaris"
    BAR = barrier
    EXTRALIBS = -lpthread -lrt
endif

OUTPUT_DIR = $(ROOT)/build/threads
PROGS = badexit2 cleanup exitstatus threadid goodexit2

all: $(OUTPUT_DIR) $(PROGS) $(OUTPUT_DIR)/condvar.o $(OUTPUT_DIR)/maketimeout.o $(OUTPUT_DIR)/mutex1.o $(OUTPUT_DIR)/mutex2.o $(OUTPUT_DIR)/mutex3.o $(OUTPUT_DIR)/rwlock.o $(TLOCK) $(BAR)

%: %.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(OUTPUT_DIR)/$@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/condvar.o: condvar.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/maketimeout.o: maketimeout.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/mutex1.o: mutex1.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/mutex2.o: mutex2.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/mutex3.o: mutex3.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/rwlock.o: rwlock.c
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
	rm -f $(PROGS) $(TEMPFILES) *.o $(TLOCK) $(BAR)

include $(ROOT)/Make.libapue.inc
