#include "gary.h"
#include "compiler.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void compile(char *c, FILE *out) {

    fputs("org 100h\n", out);

    while(*c != '\0') {

        if(*c == '"') {
            int jump_id = uid();
            fprintf(out, "jmp _skip%d\n_literal%d: dw ", jump_id, uid());

            do {
                fputc(*c, out);
                c++;
            } while(*c != '"');

            /*char *token;
            tokenizer()*/

            //print_literal(c, tokenizer, out);
            print_literal(c, is_string, out);

            fprintf(out, "\"\n_skip%d:\n", jump_id);
        } else
        if(*c >= '0' && *c <= '9') {
            int jump_id = uid();
            fprintf(out, "jmp _skip%d\n_literal%d: dw ", jump_id, uid());

            do {
                fputc(*c, out);
                c++;
            } while(*c >= '0' && *c <= '9');

            fprintf(out, "\"\n_skip%d:\n", jump_id);

            print_literal(c, is_number, out);
        } else
        if(IS_ALPHA(*c)) {
            
        }

        c++;
    }
}

void print_literal(char *c, bool (*condition)(char *), FILE *out) {
    int jump_id = uid();
    int literal_id = uid();

    fprintf(out, 
        "jmp _skip%d\n"
        "_literal%d: dw %s\n"
        "_skip%d:\n"
        "push _literal%d",
    jump_id, literal_id, tokenizer(c, condition), jump_id, literal_id);
}

char *tokenizer(char *c, bool (*condition)(char)) {
    char *ret;

    char *copy = c;
    size_t size = 0;

    do {
        size++;
        copy++;
    } while (condition(*copy));

    ret = malloc(size);
    memcpy(ret, c, size);

    return ret;
}

bool is_string(char c) {
    return c != '"';
}

bool is_number(char c) {
    return (c >= '0' && c <= '9');
}
