// eratosthenes.c
// Řešení IJC-DU1, příklad a), 22.3.2022
// Autor: Matyáš Strelec, FIT
// Přeloženo: clang 13.1.6

#include <math.h>
#include <stdio.h>

#include "eratosthenes.h"

void Eratosthenes(bitset_t bitset)
{
    bitset_setbit(bitset, 0, 1);
    bitset_setbit(bitset, 1, 1);

    unsigned long size = bitset_size(bitset);

    for (bitset_index_t i = 2; i < sqrt(size); i++)
    {
        if(bitset_getbit(bitset, i) == 0)
        {
            for (bitset_index_t j = i*i; j < size; j = j+i)
            {
                bitset_setbit(bitset, j, 1);
            }
        }
    }
}
