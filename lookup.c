#include "lookup.h"

#include <string.h>

bool SymbolList_contains(struct DynStrArray *sl, char *token) {
    for(int i = 0; i < sl->used; i++) {
        if(strcmp(sl->items[i], token)) {
            return true;
        }
    }
    return false;
}

struct SymbolLookup {
    char *symbol;
    char *equiv;
} symbols[] = {
    "@", "__gary_assignment",
    "+", "__gary_addition",
    "-", "__gary_subtraction",
    "*", "__gary_multiplication",
    "/", "__gary_division",
    "^", "__gary_exponent",
    "print", "__gary_print",
    "printint", "__gary_printint",
    "=", "__gary_equals",
    "&", "__gary_and"
};
char *symbol_lookup(char *sym) {
    for(int i = 0; i < 10; i++) {
        if(strcmp(sym, symbols[i].symbol) == 0) {
            return symbols[i].equiv;
        }
    }
    return sym;
}

bool is_string(char c) {return c != '"';}
bool is_number(char c) {return (c >= '0' && c <= '9');}
bool is_brace (char c) {return c == '{';}
bool is_symbol(char c) {
    return
        (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c == '@') ||
        (c == '+') ||
        (c == '-') ||
        (c == '*') ||
        (c == '/') ||
        (c == '&') ||
        (c == '=');
};