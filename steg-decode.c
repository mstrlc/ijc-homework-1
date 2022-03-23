// steg-decode.c
// Řešení IJC-DU1, příklad b), 22.3.2022
// Autor: Matyáš Strelec, FIT
// Přeloženo: clang 13.1.6

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "ppm.h"
#include "bitset.h"
#include "eratosthenes.h"
#include "error.h"

#define N 29 // Prime to start decoding at

int main(int argc, char *argv[])
{
    if (argc != 2) 
        error_exit("steg-decode: Špatný počet argumentů.\n");

    struct ppm *image = ppm_read(argv[1]);
	if (image == NULL)
	{
		warning_msg("steg-decode: Soubor %s se nepodařilo otevřít.\n", argv[1]);
		return -1;
	}

    unsigned long imagesize = image->xsize * image->ysize * 3;

    bitset_alloc(bitset, imagesize);
    Eratosthenes(bitset);

    char print_byte;
    int shift = 0;
    bool correctly_ended = false;

    for (bitset_index_t i = N; i < imagesize; i++) // Go through all primes starting from given number
    {
        if(bitset_getbit(bitset, i) == 0)   // Prime is found on this index
        {
            // Get the LSB of the image data on the index by using AND with 1
            // Shift the bit so it is in front of all the existing bits
            // Add it to existing bits in print_byte by using OR
            print_byte |= (image->data[i] & 1) << shift; 
            shift++;    // Increment shift

            if (shift == CHAR_BIT) // Full byte has been filled and is ready to print
            {
                printf("%c", print_byte);

                if (print_byte == '\0')
                {   
                    correctly_ended = true;
                    break;
                }

                print_byte = '\0';  // Reset the printed byte to be 0 again
                shift = 0;          // Reset the shift
            }
        }
    }

    if(!correctly_ended)
    {
        bitset_free(bitset);
        ppm_free(image);
        error_exit("steg-decode: Zpráva nebyla ukončena znakem \\0.");
    }
    
    bitset_free(bitset);
    ppm_free(image);
}
