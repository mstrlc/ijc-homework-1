// error.h
// Řešení IJC-DU1, příklad b), 22.3.2022
// Autor: Matyáš Strelec, FIT
// Přeloženo: clang 13.1.6

#ifndef ERROR_H
#define ERROR_H

void warning_msg(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif
