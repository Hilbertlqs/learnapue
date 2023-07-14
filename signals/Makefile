ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

CLD =

ifeq "$(PLATFORM)" "linux"
	CLD = child
endif
ifeq "$(PLATFORM)" "solaris"
	CLD = child
endif

OUTPUT_DIR = $(ROOT)/build/signals
PROGS = critical mask read1 read2 reenter sigtstp sigusr suspend1 suspend2 sig2str test_sig_sync test_sleep mycat_mod test_fwrite
MOREPROGS = $(OUTPUT_DIR)/systest2 $(OUTPUT_DIR)/tsleep2

#all: $(OUTPUT_DIR) $(PROGS) $(MOREPROGS) $(OUTPUT_DIR)/abort.o $(OUTPUT_DIR)/sleep1.o $(OUTPUT_DIR)/sleep2.o $(CLD)
all: $(OUTPUT_DIR) $(PROGS) $(MOREPROGS) $(OUTPUT_DIR)/abort.o $(OUTPUT_DIR)/sleep1.o $(OUTPUT_DIR)/sleep2.o $(OUTPUT_DIR)/system.o $(CLD)

%: %.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(OUTPUT_DIR)/$@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/abort.o: abort.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/sleep1.o: sleep1.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/sleep2.o: sleep2.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/tsleep2.o: tsleep2.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/tsleep2: $(OUTPUT_DIR)/tsleep2.o $(OUTPUT_DIR)/sleep2.o $(LIBAPUE)
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/tsleep2 $(OUTPUT_DIR)/tsleep2.o $(OUTPUT_DIR)/sleep2.o $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/system.o: system.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/systest2.o: systest2.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

#$(OUTPUT_DIR)/systest2: $(OUTPUT_DIR)/systest2.o $(ROOT)/build/proc/system.o $(LIBAPUE)
#	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/systest2 $(OUTPUT_DIR)/systest2.o $(ROOT)/build/proc/system.o $(LDFLAGS) $(LDLIBS)
$(OUTPUT_DIR)/systest2: $(OUTPUT_DIR)/systest2.o $(OUTPUT_DIR)/system.o $(LIBAPUE)
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/systest2 $(OUTPUT_DIR)/systest2.o $(OUTPUT_DIR)/system.o $(LDFLAGS) $(LDLIBS)

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
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o file.hole $(CLD)

include $(ROOT)/Make.libapue.inc
