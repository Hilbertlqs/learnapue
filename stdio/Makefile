ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "linux"
	MEMSTR = memstr
else
	MEMSTR = 
endif

OUTPUT_DIR = $(ROOT)/build/stdio
PROGS = buf fgetsfputs getcharbug getcputc mkstemp tempfiles fgetcfputc

all: $(OUTPUT_DIR) $(PROGS) $(MEMSTR) my_setbuf fflush_fsync_test

%: %.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(OUTPUT_DIR)/$@ $(LDFLAGS) $(LDLIBS)

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
	rm -f $(PROGS) $(TEMPFILES) *.o $(MEMSTR)

include $(ROOT)/Make.libapue.inc
