// primes.c
// Řešení IJC-DU1, příklad a), 22.3.2022
// Autor: Matyáš Strelec, FIT
// Přeloženo: clang 13.1.6

#include <stdio.h>
#include <time.h>

#include "bitset.h"
#include "eratosthenes.h"

#define N 300000000

int main() {
    clock_t start = clock();

    bitset_create(bitset, N);
    Eratosthenes(bitset);

    unsigned long primes_to_print[10] = {0, };
    int primes_index = 0;

    for (bitset_index_t i = N - 1; i > 0 && primes_index < 10; i--)
    {
        if (bitset_getbit(bitset, i) == 0)
        {
            primes_to_print[primes_index] = i;
            primes_index++;
        }
    }
    
    for(int i = 9; i >= 0; i--)
    {
        printf("%lu\n", primes_to_print[i]);
    }

    fprintf(stderr, "Time=%.3g\n", (double) (clock() - start) / CLOCKS_PER_SEC);
    
    return 0;
}
