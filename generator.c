#include "generator.h"
#include "compiler.h"
#include "lookup.h"
#include "gary.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * Prints: a memory block for a literal value and a push statement to put
 * the literal value on the stack.
 *
 * Techincally number literals could just be pushed directly onto the stack,
 * but this a one-size-fits-all method that works for strings and numbers.
 *
 * char *token here would be the literal value itself.
 * int sub_id tells us what scope the code is currently in (subroutine ID) so
 * variables with the same name can be created in different scopes and cannot
 * be accessed outside the scope.
 */
void print_Literal(char *token, int sub_id, FILE *out) {
    /* uid is a function that returns a new, unique number every time */
    int jump_id = uid();
    int literal_id = uid();

    fprintf(out,
        "jmp _skip%d\n"
        "__sub%d_literal%d: dw %s%s\n"
        "_skip%d:\n"
        "push __sub%d_literal%d\n",
    jump_id, sub_id, literal_id, token,
    (*token == '\"' ? "\", 0" : " "),
    /* ^ if this is a string, put the closing quote on */
    jump_id, sub_id, literal_id);
}

/**
 * Prints a symbol, or rather a variable name.
 *
 * symbol_list is a Dynamic String Array that holds all the symbols seen
 * with their respective sub_ids as to differentiate between scopes.
 *
 * Each encountere symbol (found in char *token) is checked against symbol_list.
 * If it's found, then the value to the symbol is pushed to the stack. If not,
 * then memory for the symbol is created and its pointer is pushed to the stack,
 * hopefully to be passed to a __gary_assignment call so the actual value of
 * the variable can be defined.
 */
void print_Symbol(char *token, int sub_id, struct DynStrArray *symbol_list, FILE *out) {
    char true_token[30];
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

/**
 * A call expression is marked off by a | character. The token after this
 * is assumed to be the name of a function, and is thus passed into this
 * function.
 *
 * The token is checked against a symbol lookup table which contains a list
 * of all of the stdlib functions and the actual assembly names they correspond
 * to (e.g. @ = __gary_assignment).
 *
 * If the variable is a stdlib function, it's equivalent assembly named is
 * "call"ed. If it's not, the function is assumed to be in the local scope, and
 * thus is called with the prefix __sub#d_. If the function was indeed declared
 * in the local scope, then its generated assembly code would have a matching
 * prefix.
 */
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
 * This function differs from the other generation functions because it doesn't
 * take a token, but rather it takes the pointer to the pointer to the code.
 * This is done very simply for ease -- this function can advance the pointer
 * past the parameter block, rather than having to tell the callee to do it.
 * (This latter method was tried at first and it turned out to be very messy).
 *
 * This subroutine makes use of a Dynamic String Array as a stack because
 * the parameters listed in the parameter block need to be "pop"ped off in
 * reverse order since the parameters are going to be pushed onto the stack
 * before the function "call" in the order that the parameter block has them.
 *
 *
 */
void print_ParamBlock(char **c, int sub_id, struct DynStrArray *symbol_list, FILE *out) {
    struct DynStrArray pb;
    DynStrArray_init(&pb);

    /* Store the instruction pointer from the stack for later. */
    int jump1_id = uid();
    int jump2_id = uid();
    fprintf(out,
        "jmp _skip%d\n"
        "__sub%d_ip: dw 0\n"
        "_skip%d:\n"
        "pop word [__sub%d_ip]\n"
        "jmp _skip%d\n",
    jump1_id, sub_id, jump1_id, sub_id, jump2_id);

    /* Print out the memory block for the parameters. */
    char true_param[30];
    while(**c != ':') {
        skip_until(c, is_symbol);

        char *param;
        read_token(&param, c, is_symbol);

        fprintf(out,
            "__sub%d_%s: dw 0\n"
            "__sub%d_%s_ptr: dw __sub%d_%s\n",
        sub_id, param, sub_id, param, sub_id, param);
        DynStrArray_add(&pb, param);

        sprintf(true_param, "__sub%d_%s", sub_id, param);
        DynStrArray_add(symbol_list, true_param);
    }

    /* Print out the pop statements in reverse order. */
    fprintf(out, "_skip%d:\n", jump2_id);
    for(int i = pb.used; i > 0; i--) {
        fprintf(out, "pop word [__sub%d_%s]\n", sub_id, *(pb.items + i - 1));
    }
}

/**
 * A very basic tokenizing function.
 *
 * **token is a pointer to a string. This function *reads* the next token
 * directly into the string. The original design had this function return a
 * pointer, but it was very messy.
 *
 * bool (*condition)(char) is a pointer to a function, that given a variable,
 * returns whether that character matches the right format for the desired
 * token.
 *
 * For example, the is_number function can be passed here. Then, the call
 * read_token(..., is_number) would set **token to be a string containing
 * the next characters in *c that were numberes.
 */
void read_token(char **token, char **c, bool (*condition)(char)) {
    char *ptr = *c;
    size_t size = 0;

    do {
        size++;
        ptr++;
    } while (condition(*ptr));

    *token = malloc(size+1);
    memcpy(*token, *c, size);

    /* null-terminate the string so that it can be printed out. */
    (*token)[size] = '\0';

    *c = ptr;
}