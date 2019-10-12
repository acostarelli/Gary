#include "gary.h"
#include "tokenizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tokenize(char *code, struct TokenArray *ta) {
    int current_depth = 0;

    while(*code != '\0') {
        struct Token t;

        /* Template code; to be overridden as needed */
        t.type = LITERAL;
        t.value = code;
        t.value_length = 1;
        t.depth = current_depth;

        /*if(IS_WHITESPACE(c)) {
            continue;
        }*/

        /* Literals */
        if(IS_NUMBER(*code)) {
            while(IS_NUMBER(*(code+1))) {
                t.value_length++;
                code++;
            }
            TokenArray_add(ta, &t);
        } else
        if(IS_LETTER(*code)) {
            while(IS_LETTER(*(code+1))) {
                t.value_length++;
                code++;
            }
            TokenArray_add(ta, &t);
        } else
        if(IS_QUOTE(*code)) {
            while(!IS_QUOTE(*(code+1))) {
                t.value_length++;
                code++;
            }
            t.value_length++; // TODO Condense this
            code++; // so that we don't pick it up the next time
            TokenArray_add(ta, &t);
        } else {
            /* Expressions. TODO: Factor */
            t.type = EXPRESSION;
            switch(*code) {
                case '(':
                case '{': {
                    current_depth++;

                    TokenArray_add(ta, &t);
                    break;
                }
                case ')':
                case '}': {
                    current_depth--; // can ignore closing expression markers
                    break;
                }
                case '+':
                case '-':
                case '*':
                case '/':
                case '@':
                case ':': {
                    current_depth++;

                    struct Token last = TokenArray_pop(ta);
                    last.depth = current_depth;

                    TokenArray_add(ta, &t);
                    TokenArray_add(ta, &last);

                    current_depth--;
                    break;
                }
            }
        }

        code++;
    }
}

struct Token TokenArray_pop(struct TokenArray *ta) {
    struct Token ret = ta->tokens[ta->used-1];
    //free(&ta->tokens[ta->used-1]);
    ta->used = ta->used - 1;

    return ret;
}

void TokenArray_init(struct TokenArray *ta) {
    ta->tokens = malloc(1 * sizeof(struct Token));
    ta->used = 0;
    ta->size = 1;
}

void TokenArray_add(struct TokenArray *ta, struct Token *t) {
    if(ta->used == ta->size) {
        ta->size = ta->size * 2;
        ta->tokens = realloc(ta->tokens, ta->size * sizeof(struct Token));
    }

    ta->tokens[ta->used++] = *t;
}

void TokenArray_clear(struct TokenArray *ta) {
    free(ta->tokens);
    ta->tokens = NULL;

    ta->used = 0;
    ta->size = 0;
}

void TokenArray_print(struct TokenArray *ta) {
    for(int i = 0; i < ta->used; i++) {
        printf("%d: ", i);
        Token_print(&ta->tokens[i]);
        puts("\n");
    }
}

void Token_print(struct Token *t) {
    char *text = malloc(t->value_length);
    memcpy(text, t->value, t->value_length);
    printf("%s depth: %d", text, t->depth);
}
