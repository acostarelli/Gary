#include "generator.h"
#include "compiler.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *print_literal(char *c, bool (*condition)(char), int subid, FILE *out) {
    int jump_id = uid();
    int literal_id = uid();

    fprintf(out,
        "jmp _skip%d\n"
        "__sub%d_literal%d: dw ",
    jump_id, subid, literal_id);

    char *ret = print_token(c, condition, -1, out);

    /* If this is a quote, put the closing one on.*/
    if(*c == '"') {
        fputc('"', out);
    }

    fprintf(out,
        "\n_skip%d:\n"
        "push __sub%d_literal%d\n",
    jump_id, subid, literal_id);

    return ret;
}

char *print_symbol_literal(char *c, int subid, FILE *out) {
    fprintf(out, "push ");
    char *ret = print_token(c, is_symbol, subid, out);
    fputc('\n', out);

    return ret;
}

// TODO all of these print expression/literal functions have the
// same format and can probably be condensed in some way.
char *print_call_expression(char *c, int subid, FILE *out) {
    fprintf(out, "call ");
    char *ret = print_token(c, is_symbol, subid, out);
    fputc('\n', out);

    return ret;
}

char *print_function_expression(char *c, int subid, FILE *out) {
    //fprintf(out, )
    //// NEED ANOTHER STACK STRUCTURE IN ORDER TO HAVE THE
    return c;
}

char *print_parameter_block(char *c, FILE *out) {
    int subid = uid();
    char *ret;

    struct ParameterBlock pb;
    ParameterBlock_init(&pb);

    int jump_id = uid();
    fprintf(out,
        "jmp _skip%d\n"
        "__sub%d_return: dw 0\n",
    jump_id, subid);

    while(*c != ':') {
        while(!is_symbol(*c)) {
            c++;
        }
        char *symbol_start = c;

        //fprintf(out, "__sub%d_", sub_id);
        char *symbol_end = print_token(c, is_symbol, subid, out);
        fputs(": dw 0\n", out);

        ParameterBlock_add(&pb, symbol_start, ((int)symbol_end - (int)symbol_start)+1);

        c = symbol_end + 1; // don't double count the end of a symbol
    }

    fprintf(out, "_skip%d:\n", jump_id);
    for(int i = pb.used; i > 0; i--) {
        printf("pop __sub%d_%s\n", subid, *(pb.parameters + i - 1));
    }

    return c;
}

// would be much better if it just returned the string so the code
// generator functions wouldn't need to be so jagged
char *print_token(char *c, bool (*condition)(char), int subid, FILE *out) {
    char *print;

    char *ptr = c;
    size_t size = 0;

    do {
        size++;
        ptr++;
    } while (condition(*ptr));

    print = malloc(size);
    memcpy(print, c, size);
    char *symbol = symbol_lookup(print);

    //printf("Comparison between: %s and %s = %d\n", symbol, print, strcmp(symbol, print));

    /**
     * If we're in a subroutine...
     * and the symbol referenced is not a reserved symbol...
     * then give it a prefix to indicate which subroutine it's in.
     *
     * If the symbol is a reserved symbol, then sticking the sub prefix on
     * it would mean it wouldn't work properly.
     */
    if(subid != -1 && strcmp(symbol, print) == 0) {
        fprintf(out, "__sub%d_", subid);
    }

    fprintf(out, "%s", symbol);

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
void ParameterBlock_add(struct ParameterBlock *pb, char *start, size_t size) {
    if(pb->used == pb->size) {
        pb->size = pb->size * 2;
        pb->parameters = realloc(pb->parameters, pb->size * sizeof(char *));
    }

    //pb->parameters[pb->used++] = parameter;
    pb->parameters[pb->used] = malloc(size);
    memcpy(pb->parameters[pb->used], start, size + 1);
    pb->parameters[pb->used][size] = '\0';
    pb->used++;
}
