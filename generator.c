#include "generator.h"
#include "compiler.h"
#include "lookup.h"
#include "gary.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void print_Literal(char *token, int sub_id, FILE *out) {
    int jump_id = uid();
    int literal_id = uid();

    fprintf(out,
        "jmp _skip%d\n"
        "__sub%d_literal%d: dw %s%s\n"
        "_skip%d:\n"
        "push __sub%d_literal%d\n",
    jump_id, sub_id, literal_id, token,
    (*token == '\"' ? "\", 0" : " "),
    // ^ if this is a string, put the closing quote on
    jump_id, sub_id, literal_id);
}

/**
Problems:
- needs to treat variable names like __sub_[name]
- needs to consider parameters
*/
void print_Symbol(char *token, int sub_id, struct DynStrArray *symbol_list, FILE *out) {
    //char *true_token = malloc(strlen(token) + strlen("__sub_") + strlen(itoa(sub_id)) + 1);
    char true_token[20];
    sprintf(true_token, "__sub%d_%s", sub_id, token);

    if(DynStrArray_contains(symbol_list, true_token)) {
        fprintf(out, "push word [%s_ptr]\n", true_token);
    } else {
        int jump_id = uid();
        fprintf(out,
            "jmp _skip%d\n"
            "%s: dw 0\n"
            "%s_ptr: dw %s\n"
            "_skip%d:\n"
            "push %s_ptr\n",
        jump_id, true_token, true_token, true_token, jump_id, true_token);

        DynStrArray_add(symbol_list, true_token);
    }
}

void print_CallExp(char *token, int sub_id, FILE *out) {
    char *symbol = symbol_lookup(token);

    if(strcmp(symbol, token) == 0) {
        fprintf(out, "call __sub%d_%s\n", sub_id, token);
    } else {
        fprintf(out, "call %s\n", symbol);
    }
    fputs("push ax\n", out);
}

/**
 * - Unfortunate that this modifies *c
 * - Needs to add its variables to the symbol list
 * - Need to handle the instruction pointer somehow
 *      - pop it from the stack, put it in a variable, push it before the
          function returns
 */

void print_ParamBlock(char **c, int sub_id, struct DynStrArray *symbol_list, FILE *out) {
    char *ret;

    struct DynStrArray pb;
    DynStrArray_init(&pb);

    int jump1_id = uid();
    int jump2_id = uid();
    fprintf(out,
        "jmp _skip%d\n"
        "__sub%d_ip: dw 0\n"
        "_skip%d:\n"
        "pop word __sub%d_ip\n"
        "jmp _skip%d\n",
    jump1_id, sub_id, jump1_id, sub_id, jump2_id);

    while(**c != ':') {
        skip_until(c, is_symbol);

        char *param;
        read_token(&param, c, is_symbol);

        fprintf(out, "__sub%d_%s: dw 0\n", sub_id, param);
        DynStrArray_add(&pb, param);

        char true_param[20];
        sprintf(true_param, "__sub%d_%s", sub_id, param);
        DynStrArray_add(symbol_list, true_param);
    }

    fprintf(out, "_skip%d:\n", jump2_id);
    for(int i = pb.used; i > 0; i--) {
        fprintf(out, "pop word [__sub%d_%s]\n", sub_id, *(pb.items + i - 1));
    }
}

void read_token(char **token, char **c, bool (*condition)(char)) {
    char *ptr = *c;
    size_t size = 0;

    do {
        size++;
        ptr++;
    } while (condition(*ptr));

    *token = malloc(size+1);
    memcpy(*token, *c, size);
    (*token)[size] = '\0';

    *c = ptr;
}
