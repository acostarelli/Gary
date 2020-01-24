#ifndef GENERATOR
#define GENERATOR

#include "gary.h"

#include <stdbool.h>
#include <stdio.h>

void read_token(char **token, char **c, bool (*condition)(char));

void print_Literal(char *token, int sub_id, FILE *out);


/**
Problems:
- needs to treat variable names like __sub_[name]
- needs to consider parameters
*/
void print_Symbol(char *token, int sub_id, struct DynStrArray *symbol_list, FILE *out);
void print_CallExp(char *token, int sub_id, FILE *out);

/**
 * - Unfortunate that this modifies *c
 * - Needs to add its variables to the symbol list
 * - Need to handle the instruction pointer somehow
 *      - pop it from the stack, put it in a variable, push it before the
          function returns
 */

void print_ParamBlock(char **c, int sub_id, struct DynStrArray *symbol_list, FILE *out);
void print_Conditional(char **c, int sub_id, FILE *out);
char *print_function_expression(char *c, int subid, FILE *out);

char *print_symbol_literal(char *c, int subid, struct DynStrArray *symbol_list, FILE *out);

#endif