#include "gary.h"
#include "tokenizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tokenize(char *code, struct TokenArray *ta) {
    while(*code != '\0') {
        struct Token t;

        if(IS_NUMBER(*code)) {
            t.name = NUMBER;
            t.value = code;
            t.value_length = 1;

            while(IS_NUMBER(*(code+1))) {
                t.value_length++;
                code++;
            }

            TokenArray_add(ta, &t);
        } else
        if(IS_LETTER(*code)) {
            t.name = NAME;
            t.value = code;
            t.value_length = 1;

            while(IS_LETTER(*(code+1))) {
                t.value_length++;
                code++;
            }

            TokenArray_add(ta, &t);

        } else
        if(IS_OPERATOR(*code)) {
            t.name = OPERATOR;
            t.value = code;
            t.value_length = 1;
            TokenArray_add(ta, &t);
        } else
        if(IS_PAREN(*code)) {
            t.name = PAREN;
            t.value = code;
            t.value_length = 1;
            TokenArray_add(ta, &t);
        } else
        if(IS_QUOTE(*code)) {
            t.name = STRING;
            t.value = code;
            t.value_length = 1;

            while(!IS_QUOTE(*(code+1))) {
                t.value_length++;
                code++;
            }

            TokenArray_add(ta, &t);
        } else
        if(IS_BRACE(*code)) {
            t.name = BRACE;
            t.value = code;
            t.value_length = 1;
            TokenArray_add(ta, &t);
        } else
        if(IS_COLON(*code)) {
            t.name = COLON;
            t.value = code;
            t.value_length = 1;
            TokenArray_add(ta, &t);
        }
        else {
            // ignore
        }

        code++;
    }
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
    printf("%s", text);
}
