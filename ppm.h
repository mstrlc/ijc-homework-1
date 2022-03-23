// ppm.h
// Řešení IJC-DU1, příklad b), 22.3.2022
// Autor: Matyáš Strelec, FIT
// Přeloženo: clang 13.1.6

#ifndef PPM_H
#define PPM_H

struct ppm {
        unsigned xsize;
        unsigned ysize;
        char data[];    // RGB bajty, celkem 3*xsize*ysize
};

struct ppm * ppm_read(const char * filename);

void ppm_free(struct ppm *p);

#endif // PPM_H
