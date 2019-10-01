#include "gary.h"
#include "tokenizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tokenize(char *code, TokenArray *ta) {
    while(*(code++) != '\0') {
        Token t;

        if(IS_NUMBER(*code)) {
            puts("number");

            t.name = NUMBER;
            t.value = code;
            t.value_length = 0;

            while(IS_NUMBER(*(code++))) {
                t.value_length++;
            }

            TokenArray_add(ta, &t);
        } else
        if(IS_LETTER(*code)) {
            puts("letter");

            t.name = LETTER;
            t.value = code;
            t.value_length = 0;

            while(IS_LETTER(*(code++))) {
                t.value_length++;
            }

            TokenArray_add(ta, &t);

        } else
        if(IS_OPERATOR(*code)) {
            puts("operator");

            t.name = OPERATOR;
            t.value = code;
            t.value_length = 1;
            TokenArray_add(ta, &t);
        } else
        if(IS_PAREN(*code)) {
            puts("parenthesis");

            t.name = PAREN;
            t.value = code;
            t.value_length = 1;
            TokenArray_add(ta, &t);
        } else
        if(IS_QUOTE(*code)) {

        }
        else {
            puts("other");
            // ignore
        }
    }
}

void TokenArray_init(TokenArray *ta, size_t size) {
    ta->tokens = malloc(size * sizeof(Token));
    ta->used = 0;
    ta->size = size;
}

void TokenArray_add(TokenArray *ta, Token *t) {
    if(ta->used == ta->size) {
        ta->size = ta->size * 2;
        ta->tokens = realloc(ta->tokens, ta->size * sizeof(Token));
    }

    ta->tokens[ta->used++] = *t;
}

void TokenArray_clear(TokenArray *ta) {
    free(ta->tokens);
    ta->tokens = NULL;

    ta->used = 0;
    ta->size = 0;
}
