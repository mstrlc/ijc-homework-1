// bitset.h
// Řešení IJC-DU1, příklad a), 22.3.2022
// Autor: Matyáš Strelec, FIT
// Přeloženo: clang 13.1.6

#ifndef BITSET_H
#define BITSET_H

#include <assert.h>
#include <stdlib.h>
#include <limits.h>

#include "error.h"

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

// Macros that cannot be replaced by inline functions

#define bitset_create(jmeno_pole, velikost) \
     static_assert(velikost > 0, "Velikost pole musí být větší než 0"); \
     unsigned long (jmeno_pole)[((velikost) / (sizeof(unsigned long) * CHAR_BIT) + ((velikost) % (sizeof(unsigned long) * CHAR_BIT) == 0 ? 0 : 1) + 1)] = {(velikost), 0, }

#define bitset_alloc(jmeno_pole, velikost) \
     assert(velikost > 0); \
     bitset_t (jmeno_pole) = calloc(((velikost) / (sizeof(unsigned long) * CHAR_BIT) + ((velikost) % (sizeof(unsigned long) * CHAR_BIT) == 0 ? 0 : 1) + 1), sizeof(bitset_index_t)); \
     if(jmeno_pole == NULL) error_exit("bitset_alloc: Chyba alokace paměti"); \
     jmeno_pole[0] = (velikost);

#ifdef USE_INLINE

// Inline functions used instead of macros

static inline void bitset_free(bitset_t jmeno_pole)
{
     if((jmeno_pole) != NULL)
     {
          free(jmeno_pole);
     }
}

static inline bitset_index_t bitset_size(bitset_t jmeno_pole)
{
    return jmeno_pole[0];
}

static inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz)
{
     if(index >= bitset_size(jmeno_pole))
     {
          error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole));
     }
     else
     {
          if(vyraz == 1)
          {
               jmeno_pole[(index) / (sizeof(unsigned long) * CHAR_BIT) + 1] |= (1UL << ((index) % (sizeof(unsigned long) * CHAR_BIT)));
          }
          else
          {
               jmeno_pole[(index) / (sizeof(unsigned long) * CHAR_BIT) + 1] &= ~(1UL << ((index) % (sizeof(unsigned long) * CHAR_BIT)));
          }
     }     
}

static inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index)
{
     if(index >= bitset_size(jmeno_pole))
     {
          error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole));
          return -1;
     }
     else
     {
          return ((((jmeno_pole)[(index) / (sizeof(unsigned long) * CHAR_BIT) + 1]) & (1UL << ((index) % (sizeof(unsigned long) * CHAR_BIT)))) ? 1 : 0);
     }
}

#else

// Macros instead of inline functions

#define bitset_free(jmeno_pole) \
     do { if((jmeno_pole) != NULL) \
          free(jmeno_pole); \
    } while(0)

#define bitset_size(jmeno_pole) \
     jmeno_pole[0]

#define bitset_setbit(jmeno_pole, index, vyraz) \
     ((index >= bitset_size(jmeno_pole)) ? \
     (error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole)), 0) : \
     ((vyraz == 1) ? \
     (jmeno_pole[(index) / (sizeof(unsigned long) * CHAR_BIT) + 1] |= (1UL << ((index) % (sizeof(unsigned long) * CHAR_BIT)))) : \
     (jmeno_pole[(index) / (sizeof(unsigned long) * CHAR_BIT) + 1] &= ~(1UL << ((index) % (sizeof(unsigned long) * CHAR_BIT))))))
         
#define bitset_getbit(jmeno_pole, index) \
     ((index >= bitset_size(jmeno_pole)) ? \
     (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole)), 0) : \
     ((((jmeno_pole)[(index) / (sizeof(unsigned long) * CHAR_BIT) + 1]) & (1UL << ((index) % (sizeof(unsigned long) * CHAR_BIT)))) ? 1 : 0))

#endif
#endif
