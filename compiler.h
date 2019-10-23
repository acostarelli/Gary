#ifndef COMPILER
#define COMPILER

#include <stdio.h>
#include <stdbool.h>

void compile(char *c, FILE *out);
void print_compiled(char **c, int subid, FILE *out);
void skip_until(char **c, bool (*condition)(char));

#endif
