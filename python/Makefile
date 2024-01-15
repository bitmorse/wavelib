CC=gcc
CFLAGS=-I. -fPIC  # -fPIC is needed for shared libraries
LDFLAGS=-L. -L../Bin -lwavelib -lm
SHARED=-shared  # Flag to create shared library

libwavelibwrapper.so: main.o
	$(CC) $(SHARED) -o libwavelibwrapper.so main.o $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

clean:
	rm -f libwavelibwrapper.so main.o main

.PHONY: clean
