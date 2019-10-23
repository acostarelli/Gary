#ifndef GENERATOR
#define GENERATOR

#include "gary.h"

#include <stdbool.h>
#include <stdio.h>

#define PTR_RANGE(start, end) (((int)end - (int)start) + 1)

//char *print_token(char *c, bool (*condition)(char), int subid, FILE *out);

void read_token(char **token, char **c, bool (*condition)(char));

/**
 * Returns what ought be the new code pointer so that code isn't reread.
 */
void print_Literal(char *token, int sub_id, FILE *out);
void print_Symbol(char *token, int sub_id, struct DynStrArray *symbol_list, FILE *out);
void print_CallExp(char *token, int sub_id, FILE *out);
void print_ParamBlock(char **c, int sub_id, FILE *out);
char *print_function_expression(char *c, int subid, FILE *out);

char *print_symbol_literal(char *c, int subid, struct DynStrArray *symbol_list, FILE *out);

#endif
