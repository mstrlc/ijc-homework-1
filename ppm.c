// ppm.c
// Řešení IJC-DU1, příklad b), 22.3.2022
// Autor: Matyáš Strelec, FIT
// Přeloženo: clang 13.1.6

#include <stdlib.h>
#include <stdio.h>

#include "ppm.h"
#include "error.h"

struct ppm *ppm_read(const char * filename)
{
	FILE* f = fopen(filename, "r");
	if(f == NULL)
    {
		warning_msg("ppm_read: Soubor %s se nepodařilo otevřít.\n", filename);
		return NULL;
	}

    int x, y, maxsize;
	fscanf(f, "P6 %d %d %d\n", &x, &y, &maxsize);

	unsigned long imagesize = x * y * 3;

	struct ppm *image = malloc(sizeof(struct ppm) + imagesize);
	if (image == NULL)
	{
		fclose(f);
		warning_msg("ppm_read: Chyba alokace paměti.\n");
		return NULL;
	}

	image->xsize = x;
	image->ysize = y;

    if(fread(image->data, sizeof(char), imagesize, f) < imagesize)
	{
		free(image);
		fclose(f);
		warning_msg("ppm_read: Chyba formátu souboru.\n");
		return NULL;
	}

	fclose(f);
	return image;
}

void ppm_free(struct ppm *p)
{
	if (p != NULL)
	{
		free(p);
	}
}
