#include "gary.h"
#include "compiler.h"
#include "generator.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**

TODO:
- Write your own subroutine handling code. I don't think ret and stuff would work.
- If it's the first time seeing a symbol in a scope, create some
blank memory for that symbol.
- Fix the : code. You've might've done that with the break statement already
but just check anyway.

*/

#define DEBUG puts("------------------");

static struct Stack sub_stack;

void compile(char *c, FILE *out) {
    puts("org 100h\n");
    DEBUG;

    /*while(*c != '\0') {
        c = print_compiled(c, out);
        c++;
    }*/

    Stack_init(&sub_stack);

    print_compiled(c, out);
}

char *print_compiled(char *c, FILE *out) {
    while(*c != '\0') {
        if(*c == '"') {
            c = print_literal(c, is_string, out);
            c++; // skip the ending quote
            DEBUG;
        } else
        if(is_number(*c)) {
            c = print_literal(c, is_number, out);
            DEBUG;
        } else 
        if(is_symbol(*c)) {
            c = print_symbol_literal(c, out);
            DEBUG;
        } else {
            switch(*c) {
                case '|': {
                    // find next symbol
                    // print that boy
                    while(!is_symbol(*c)) {
                        c++;
                    }
                    c = print_call_expression(c, out);
                    DEBUG;

                    break;
                }
                case ':': {
                    c++; // skip past the first :
                    c = print_parameter_block(c, out);

                    break;
                }
                case '{': {
                    int jump_id = uid();
                    int sub_id = uid();

                    fprintf(out,
                        "jmp _skip%d\n"
                        "*****_sub%d:\n",
                    jump_id, sub_id);

                    DEBUG;

                    Stack_push(&sub_stack, sub_id);
                    c = print_compiled(c+1, out);

                    fprintf(out,
                        "_skip%d:\n"
                        "push _sub%d\n",
                    jump_id, sub_id);

                    DEBUG;
                    break;
                }
                case '}': {
                    return c;
                }
                default: {
                }
            }
        }

        c++;
    }
    return 0;
}

void Stack_init(struct Stack *s) {
    s->length = 0;
}

void Stack_push(struct Stack *s, int n) {
    if(s->length == 32) {
        perror("Stack size limit reached.");
        return;
    }

    s->data[s->length] = n;
    s->length++;
}

int Stack_pop(struct Stack *s) {
    s->length--;

    return s->data[s->length];
}
