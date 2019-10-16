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

char *print_symbol_literal(char *c,  FILE *out) {
    fprintf(out, "push ");
    char *ret = print_token(c, is_symbol, out);
    fputc('\n', out);

    return ret;
}

// TODO all of these print expression/literal functions have the
// same format and can probably be condensed in some way.
char *print_call_expression(char *c, FILE *out) {
    fprintf(out, "call ");
    char *ret = print_token(c, is_symbol, out);
    fputc('\n', out);

    return ret;
}

char *print_function_expression(char *c, FILE *out) {
    //fprintf(out, )
    //// NEED ANOTHER STACK STRUCTURE IN ORDER TO HAVE THE 
    return c;
}

char *print_parameter_block(char *c, FILE *out) {
    int sub_id = uid();
    char *ret;

    /*struct ParameterBlock pb;
    ParameterBlock_init(&pb);*/

    char *pb[5];//malloc(5 * sizeof(char *));
    int pb_i = 0;

    int jump_id = uid();
    fprintf(out,
        "jmp _skip%d\n"
        "__sub%d_return: dw 0\n",
    jump_id, sub_id);

    while(*c != ':') {
        while(!is_symbol(*c)) {
            c++;
        }
        char *symbol_start = c;

        fprintf(out, "__sub%d_", sub_id);
        char *symbol_end = print_token(c, is_symbol, out);
        fputs(": dw 0\n", out);


        // IS IT A NULL POINTER THING?
        printf("%c %c %d: %d %d\n", *symbol_start, *symbol_end, ((int)symbol_end - (int)symbol_start)+1, (int)symbol_start, (int)symbol_end);


        /* For the pop statements */
        //char *token;
        memcpy((pb+(pb_i*sizeof(char*))), symbol_start, ((int)symbol_end - (int)symbol_start) + 1);
        pb_i++;

        printf("mother fucker please %s\n", pb[0]);

        puts("don't make it here");

        //printf("here %s\n", pb[pb_i - 1]);

        /*memcpy(token, symbol_start, symbol_end - symbol_start);*/
        //fprintf(out, "Arrgh! Ye token ought be %s!\n", token);

        //ParameterBlock_add(&pb, token);
        //pb[i] = token;

        c = symbol_end + 1; // don't double count the end of a symbol
    }

    fprintf(out, "_skip%d:\n", jump_id);
    // okay so it seems to me that repl.it goes full retard when you have
    // loops and structure values. If I change this < to a > as it should be,
    // the code fails at different spots every time
    for(; pb_i > 0; pb_i--) {
        //fprintf(out, "pop %s\n", pb[pb_i-1]);
        //fprintf(out, "okay %s\n", pb[pb_i-1]);
        printf("my gawd %s\n", pb[0]);
    }

    return c;
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
    fprintf(out, "%s", symbol_lookup(print));

    return ptr-1;
    //return print;
}

char *symbol_lookup(char *sym) {
    if(strcmp(sym, "@") == 0) {
        return "__gary_assignment";
    } else
    if(strcmp(sym, "+") == 0) {
        return "__gary_addition";
    } else
    if(strcmp(sym, "+") == 0) {
        return "__gary_subtraction";
    } else
    if(strcmp(sym, "+") == 0) {
        return "__gary_multiplication";
    } else
    if(strcmp(sym, "+") == 0) {
        return "__gary_division";
    } else
    if(strcmp(sym, "+") == 0) {
        return "__gary_exponent";
    } else {
        return sym;
    }
}

bool is_string(char c) {return c != '"';}
bool is_number(char c) {return (c >= '0' && c <= '9');}
bool is_symbol(char c) {
    return
        (c >= 'A' && c <= 'Z') || 
        (c >= 'a' && c <= 'z') ||
        (c == '@') ||
        (c == '+') ||
        (c == '-') ||
        (c == '*') ||
        (c == '/');
};

void ParameterBlock_init(struct ParameterBlock *pb) {
    pb->parameters = malloc(sizeof(char *));
    pb->used = 0;
    pb->size = 1;
}

// Does this need to be **parameter? And then you dereference it?
void ParameterBlock_add(struct ParameterBlock *pb, char *parameter) {
    if(pb->used == pb->size) {
        pb->size = pb->size * 2;
        pb->parameters = realloc(pb->parameters, pb->size * sizeof(char *));
    }

    pb->parameters[pb->used++] = parameter;
}
