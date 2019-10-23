#include "gary.h"
#include "compiler.h"
#include "generator.h"
#include "lookup.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**

TODO:
- Write your own subroutine handling code. I don't think ret and stuff would work.
- If it's the first time seeing a symbol in a scope, create some
blank memory for that symbol.
- Arrays
- Remove all comments
- Neaten up code
- Add sufficient documentation and explanation

*/

static bool IS_DEBUG = true;
#define DEBUG if(IS_DEBUG) { puts("------------------"); }

static struct Stack sub_stack;
static struct DynStrArray symbol_list;
//static struct int subid -1;

void compile(char *c, FILE *out) {
    puts("org 100h\n");
    DEBUG;

    Stack_init(&sub_stack);
    DynStrArray_init(&symbol_list);

    puts("pretty please?");

    print_compiled(&c, 0, out);
}

void print_compiled(char **c, int sub_id, FILE *out) {
    while(**c != '\0') {
        char *token;

        if(**c == '"') {
            read_token(&token, c, is_string);
            print_Literal(token, sub_id, out);
            DEBUG;
        } else
        if(is_number(**c)) {
            read_token(&token, c, is_number);
            print_Literal(token, sub_id, out);
            DEBUG;
        } else
        if(is_symbol(**c)) {
            read_token(&token, c, is_symbol);
            print_Symbol(token, sub_id, &symbol_list, out);

            DEBUG;
        } else {
            switch(**c) {
                case '|': {
                    skip_until(c, is_symbol);

                    read_token(&token, c, is_symbol);
                    print_CallExp(token, sub_id, out);
                    DEBUG;

                    break;
                }
                case ':': {
                    *c = *c + 1;
                    print_ParamBlock(c, sub_id, out);
                    DEBUG;
                    break;
                }
                case '{': {
                    int jump_id = uid();
                    sub_id = uid();
                    Stack_push(&sub_stack, sub_id);

                    fprintf(out,
                        "jmp _skip%d\n"
                        "_sub%d:\n",
                    jump_id, sub_id);

                    *c = *c + 1; // don't double-count the {
                    print_compiled(c, sub_id, out);

                    fprintf(out,
                        "_skip%d:\n"
                        "push _sub%d\n",
                    jump_id, sub_id);

                    DEBUG;
                    break;
                }
                case '}': {
                    return;
                }
                default: {
                }
            }
        }

        *c = *c + 1;
    }
    return;
}

void skip_until(char **c, bool (*condition)(char)) {
    while(!condition(**c)) {
        *c = *c + 1;
    }
}
