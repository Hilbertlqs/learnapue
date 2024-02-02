ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

OUTPUT_DIR = $(ROOT)/build/daemons
PROGS = test_daemonize

all: $(OUTPUT_DIR) $(PROGS) $(OUTPUT_DIR)/init.o $(OUTPUT_DIR)/reread.o $(OUTPUT_DIR)/reread2.o $(OUTPUT_DIR)/single.o

%: %.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(OUTPUT_DIR)/$@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/init.o: init.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/reread.o: reread.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/reread2.o: reread2.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/single.o: single.c
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
	rm -f $(PROGS) $(TEMPFILES) *.o
