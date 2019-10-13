#include "gary.h"
#include "compiler.h"
#include "generator.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG puts("------------------");

void compile(char *c, FILE *out) {
    puts("please");
    puts("org 100h\n");
    DEBUG;

    while(*c != '\0') {
        //printf("\nThe char: %c\n", *c);

        if(*c == '"') {
            puts("*****it's quote my guy");
            c = print_literal(c, is_string, out);
            c++; // skip the ending quote
            printf("and now it's %c \n", *c);
            DEBUG;
        } else
        if(is_number(*c)) {
            c = print_literal(c, is_number, out);
            DEBUG;
        } else {

        }

        switch(*c) {
            case '|': {
                // find next symbol
                // print that boy
                while(!is_symbol(*c)) {
                    c++;
                }
                printf("*** Started from the: %c\n", *c);
                c = print_call_expression(c, is_symbol, out);
                printf("*** Now we'we here: %c\n", *c);
                DEBUG;

                break;
            }
        }

        c++;
    }
}
