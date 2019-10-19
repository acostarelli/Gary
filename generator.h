#ifndef GENERATOR
#define GENERATOR

#include "gary.h"

#include <stdbool.h>
#include <stdio.h>

#define PTR_RANGE(start, end) (((int)end - (int)start) + 1)

char *print_token(char *c, bool (*condition)(char), int subid, FILE *out);

/**
 * Returns what ought be the new code pointer so that code isn't reread.
 */
 char *print_literal(char *c, bool (*condition)(char), int subid, FILE *out);

char *print_call_expression(char *c, int subid, FILE *out);

char *print_symbol_literal(char *c, int subid, FILE *out);

char *print_parameter_block(char *c, FILE *out);

char *print_function_expression(char *c, int subid, FILE *out);

struct ParameterBlock {
    char **parameters;
    size_t used;
    size_t size;
};
void ParameterBlock_init(struct ParameterBlock *pb);
void ParameterBlock_add(struct ParameterBlock *pb, char *start, size_t size);

/**
 * Returns the proper name for function symbol as found in
 * the standard library.
 */
char *symbol_lookup(char *sym);

bool is_string(char c);
bool is_number(char c);
bool is_symbol(char c);

#endif
