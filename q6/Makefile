CC ?= gcc
CFLAGS_common ?= -O0 -Wall -std=gnu99

EXEC = iterative recursive
all: $(EXEC)

SRCS_common = main.c

iterative: $(SRCS_common) iterative.c
	$(CC) $(CFLAGS_common) -o $@ $(SRCS_common) $@.c

recursive: $(SRCS_common) recursive.c
	$(CC) $(CFLAGS_common) -o $@ $(SRCS_common) $@.c

clean:
	$(RM) $(EXEC) *.o perf.*
