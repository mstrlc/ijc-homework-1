# Makefile
# Autor: Matyáš Strelec, FIT

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2 -fsanitize=address

.PHONY:
	clean pack all run

all: primes primes-i steg-decode

primes.o: primes.c bitset.h eratosthenes.h error.h
primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) -o $@ -lm $^
primes-i.o: primes.c bitset.h eratosthenes.h error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -o $@ -c primes.c
primes-i: primes-i.o eratosthenes-i.o error.o
	$(CC) $(CFLAGS) -o $@ -lm $^

steg-decode.o: steg-decode.c error.h bitset.h ppm.h eratosthenes.h
steg-decode: steg-decode.o error.o ppm.o eratosthenes.o
	$(CC) $(CFLAGS) -o $@ -lm $^

eratosthenes.o: eratosthenes.c bitset.h eratosthenes.h error.h
eratosthenes-i.o: eratosthenes.c bitset.h eratosthenes.h error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -o $@ -c eratosthenes.c

ppm.o: ppm.c ppm.h error.h

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o $@

run: primes primes-i
	./primes
	./primes-i

clean:
	rm *.o primes primes-i steg-decode xstrel03.zip

pack:
	zip xstrel03.zip *.h *.c Makefile
