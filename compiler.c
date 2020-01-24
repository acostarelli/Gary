#include "gary.h"
#include "compiler.h"
#include "generator.h"
#include "lookup.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void compile(char *c, FILE *out) {
    fputs("org 100h\n%include \"garystdlib.asm\"\n", out);

    /* When entering into a conditional block, recursion is NOT used unlike
    in a function definition because the conditional block is considered
    part of the same scope as its outer scope. Therefore, the same method
    for keeping track of the beginning and end of a function block can't be
    used for conditional blocks as well. Conditional blocks use this stack
    to keep track of label IDs: the conditional block in the assembly is ended
    with a label where, if the condition isn't met, the processor jumps to
    so as not to execute the code inside the conditional. */
    struct Stack skip_stack;
    struct DynStrArray symbol_list;

    Stack_init(&skip_stack);
    DynStrArray_init(&symbol_list);

    print_compiled(&c, 0, skip_stack, symbol_list, out);
}

void print_compiled(
    char **c,
    int sub_id,
    struct Stack skip_stack,
    struct DynStrArray symbol_list,
    FILE *out
) {
    bool is_conditional = false;

    while(**c != '\0') {
        char *token;

        if(**c == '"') {
            read_token(&token, c, is_string);
            print_Literal(token, sub_id, out);
        } else
        if(is_number(**c)) {
            read_token(&token, c, is_number);
            print_Literal(token, sub_id, out);
        } else
        if(is_symbol(**c)) {
            read_token(&token, c, is_symbol);
            print_Symbol(token, sub_id, &symbol_list, out);
        } else {
            switch(**c) {
                case '|': {
                    skip_until(c, is_symbol);

                    read_token(&token, c, is_symbol);
                    print_CallExp(token, sub_id, out);

                    break;
                }
                case ':': {
                    *c = *c + 1;
                    print_ParamBlock(c, sub_id, &symbol_list, out);
                    break;
                }
                case '?': {
                    int skip_id = uid();
                    fprintf(out,
                        "pop ax\n"
                        "cmp ax, 1\n"
                        "jne __gary_conditional%d\n",
                    skip_id);

                    is_conditional = true;
                    Stack_push(&skip_stack, skip_id);

                    break;
                }
                case '{': {
                    if(!is_conditional) {
                        int jump_id = uid();
                        int new_sub_id = uid();
                        fprintf(out,
                            "jmp _skip%d\n"
                            "_sub%d:\n",
                        jump_id, new_sub_id);

                        Stack_push(&skip_stack, sub_id);

                        *c = *c + 1; // don't double-count the {
                        print_compiled(c, new_sub_id, skip_stack, symbol_list, out);

                        fprintf(out,
                            "_skip%d:\n"
                            "push _sub%d\n",
                        jump_id, new_sub_id);
                    }

                    break;
                }
                case '}': {
                    if(!is_conditional) {
                        fprintf(out,
                            "mov ax, word [__sub%d_return_ptr]\n"
                            "push word [__sub%d_ip]\n"
                            "ret\n",
                        sub_id, sub_id);

                        /* If this function was called recursively due to a
                        { being encountered, then execution would return
                        above in the case '{' block after the print_compiled
                        call. */
                        return;
                    } else {
                        int last_skip = Stack_pop(&skip_stack);
                        fprintf(out, "__gary_conditional%d:\n", last_skip);
                        is_conditional = false;
                    }
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