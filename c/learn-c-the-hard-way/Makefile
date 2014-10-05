CC = gcc
CFLAGS = -Wall -g -DNDEBUG

SOURCE := $(filter-out object.c, $(wildcard *.c))
BINARIES := $(patsubst %.c, %, $(SOURCE))

all: object $(BINARIES)

object:
	$(CC) $(CFLAGS) -c -o object.o object.c

ex19:
	$(CC) $(CFLAGS) ex19.c object.o -o ex19

ex22:
	$(CC) $(CFLAGS) -c -o ex22.o ex22.c

ex22_main:
	$(CC) $(CFLAGS) ex22_main.c ex22.o -o ex22_main

%: %.c
	$(CC) $(CFLAGS) -o $@ -ldl $<

clean:
	rm -f $(BINARIES) object.o
