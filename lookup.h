#ifndef LOOKUP
#define LOOKUP

#include "compiler.h"
#include "generator.h"

#include <stdbool.h>

// TODO repetitive from print_symbol
bool SymbolList_contains_next_symbol(struct DynStrArray *sl, char *c);

/**
 * Returns the proper name for function symbol as found in
 * the standard library.
 */
char *symbol_lookup(char *sym);

bool is_string(char c);
bool is_number(char c);
bool is_symbol(char c);
bool is_brace (char c);

#endif