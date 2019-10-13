#include "generator.h"
#include "compiler.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *print_literal(char *c, bool (*condition)(char), FILE *out) {
    int jump_id = uid();
    int literal_id = uid();

    fprintf(out,
        "jmp _skip%d\n"
        "_literal%d: dw ",
    jump_id, literal_id);

    char *ret = print_token(c, condition, out);

    /* If this is a quote, put the closing one on.*/
    if(*c == '"') {
        fputc('"', out);
    }

    fprintf(out,
        "\n_skip%d:\n"
        "push _literal%d\n",
    jump_id, literal_id);

    return ret;
}

char *print_call_expression(char *c, bool(*condition)(char), FILE *out) {
    fprintf(out, "call ");
    char *ret = print_token(c, condition, out);
    fputc('\n', out);

    return ret;
}

// would be much better if it just returned the string so the code
// generator functions wouldn't need to be so jagged
char *print_token(char *c, bool (*condition)(char), FILE *out) {
    char *print;

    char *ptr = c;
    size_t size = 0;

    do {
        size++;
        ptr++;
    } while (condition(*ptr));

    print = malloc(size);
    memcpy(print, c, size);
    fprintf(out, "%s", print);

    return ptr-1;
    //return print;
}

bool is_string(char c) {return c != '"';}
bool is_number(char c) {return (c >= '0' && c <= '9');}
bool is_symbol(char c) {return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');}
