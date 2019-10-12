#ifndef COMPILER
#define COMPILER

#include <stdbool.h>

#define IS_ALPHA(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

void print_literal(char *c, bool (*condition)(char *), FILE *out);

void compile(char *code, FILE *out);

char *tokenizer(char *c, bool (*condition)(char));

bool is_string(char c);
bool is_number(char c);

#endif
