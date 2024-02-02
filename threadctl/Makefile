ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

TOUT =
ifeq "$(PLATFORM)" "freebsd"
  EXTRALIBS = -pthread
endif
ifeq "$(PLATFORM)" "linux"
  EXTRALIBS = -pthread
  TOUT = timeout.o
endif
ifeq "$(PLATFORM)" "solaris"
  EXTRALIBS = -lpthread
  TOUT = timeout.o
endif

OUTPUT_DIR = $(ROOT)/build/threadctl
PROGS =	atfork suspend

all:	$(OUTPUT_DIR) $(PROGS) $(OUTPUT_DIR)/detach.o $(OUTPUT_DIR)/getenv1.o $(OUTPUT_DIR)/getenv2.o $(OUTPUT_DIR)/getenv3.o $(OUTPUT_DIR)/$(TOUT) $(OUTPUT_DIR)/putenv_r.o $(OUTPUT_DIR)/sleep.o

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(OUTPUT_DIR)/$@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/detach.o: detach.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/$(TOUT): detach.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/getenv1.o: getenv1.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/getenv2.o: getenv2.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/getenv3.o: getenv3.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/putenv_r.o: putenv_r.c
	$(CC) $(CFLAGS) -c -fPIC $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OUTPUT_DIR)/sleep.o: sleep.c
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

include $(ROOT)/Make.libapue.inc
