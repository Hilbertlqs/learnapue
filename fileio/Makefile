ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

OUTPUT_DIR = $(ROOT)/build/fileio
PROGS = fileflags hole mycat seek my_dup2 my_dup2_list lseek_test

all: $(OUTPUT_DIR) $(PROGS) $(OUTPUT_DIR)/setfl.o $(OUTPUT_DIR)/clrfl.o

%: %.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(OUTPUT_DIR)/$@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/setfl.o: setfl.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/clrfl.o: clrfl.c
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
	rm -f $(PROGS) $(TEMPFILES) *.o file.hole

include $(ROOT)/Make.libapue.inc