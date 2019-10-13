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

char *print_call_expression(char *c, FILE *out);

char *print_symbol_literal(char *c,  FILE *out);

char *print_parameter_block(char *c, FILE *out);

char *print_function_expression(char *c, FILE *out);

struct ParameterBlock {
    char **parameters;
    size_t used;
    size_t size;
};
void ParameterBlock_init(struct ParameterBlock *pb);
void ParameterBlock_add(struct ParameterBlock *pb, char *parameter);

/**
 * Returns the proper name for function symbol as found in
 * the standard library.
 */
char *symbol_lookup(char *sym);

bool is_string(char c);
bool is_number(char c);
bool is_symbol(char c);

#endif
