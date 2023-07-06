ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ACCT=
ACCTFLAGS=
ifeq "$(PLATFORM)" "linux"
	ACCT=pracct
	ACCTFLAGS = -DHAS_AXSIG -DHAS_ACORE
endif
ifeq "$(PLATFORM)" "macos"
	ACCT=pracct
	ACCTFLAGS = -DHAS_AXSIG -DHAS_ACORE
endif
ifeq "$(PLATFORM)" "solaris"
	ACCT=pracct
	ACCTFLAGS = -DHAS_AC_STAT
endif

OUTPUT_DIR = $(ROOT)/build/proc
PROGS = echoall exec1 exec2 fork1 fork2 nice pruids tellwait1 tellwait2 test1 times1 vfork1 wait1 vfork_exit vfork_stack wait_waitid tellwait_mod tellwait_output zombie_ps cloexec_parent cloexec_child
MOREPROGS = $(OUTPUT_DIR)/systest1 $(OUTPUT_DIR)/systest3

all: $(OUTPUT_DIR) $(PROGS) $(MOREPROGS) $(OUTPUT_DIR)/system.o $(ACCT)

%: %.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(OUTPUT_DIR)/$@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/system.o: system.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/systest1.o: systest1.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/systest3.o: systest3.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/systest1: $(OUTPUT_DIR)/system.o $(OUTPUT_DIR)/systest1.o $(LIBAPUE)
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/systest1 $(OUTPUT_DIR)/systest1.o $(OUTPUT_DIR)/system.o $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/systest3: $(OUTPUT_DIR)/system.o $(OUTPUT_DIR)/systest3.o $(LIBAPUE)
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/systest3 $(OUTPUT_DIR)/systest3.o $(OUTPUT_DIR)/system.o $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/pracct: pracct.c $(LIBAPUE)
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/pracct pracct.c $(LDFLAGS) $(LDLIBS)

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
	rm -f $(PROGS) $(TEMPFILES) *.o $(ACCT)

include $(ROOT)/Make.libapue.inc
