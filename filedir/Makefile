ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "linux"
	ZAP = zap
else
	ZAP = 
endif

OUTPUT_DIR = $(ROOT)/build/filedir
PROGS = access changemod filetype umask unlink $(ZAP)
MOREPROGS = 

all: $(OUTPUT_DIR) $(PROGS) $(MOREPROGS)

%: %.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(OUTPUT_DIR)/$@ $(LDFLAGS) $(LDLIBS)

ftw8: ftw8.c $(LIBAPUE)
	$(CC) $(CFLAGS) $(NAMEMAX) ftw8.c -o $(OUTPUT_DIR)/ftw8 $(LDFLAGS) $(LDLIBS)

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
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o $(ZAP)

include $(ROOT)/Make.libapue.inc
