#include "gary.h"
#include "compiler.h"
#include "generator.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG puts("------------------");

void compile(char *c, FILE *out) {
    puts("org 100h\n");
    DEBUG;

    while(*c != '\0') {
        //printf("\nThe char: %c\n", *c);

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
                }
                case '{': {
                    //// GOING TO NEED SOME SORT OF RECURSION
                    c = print_function_expression(c, out);
                }
                default: {
                }
            }
        }

        c++;
    }
}
