#ifndef GENERATOR
#define GENERATOR

#include "gary.h"

#include <stdbool.h>
#include <stdio.h>

char *print_token(char *c, bool (*condition)(char), FILE *out);

/**
 * Returns what ought be the new code pointer so that code isn't reread.
 */
char *print_literal(char *c, bool (*condition)(char), FILE *out);


char *print_string_literal(char *c, bool (*condition)(char), FILE *out);

char *print_call_expression(char *c, bool(*condition)(char), FILE *out);


bool is_string(char c);
bool is_number(char c);
bool is_symbol(char c);

#endif
