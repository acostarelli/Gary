#include "gary.h"
#include "tokenizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tokenize(char *code, Token *first) {
    Token *prev = first; // kinda weird but it's a linked list

    while(*code != '\0') {
        Token t;

        if(IS_NUMBER(*code)) {
            t.name = NUMBER;
            t.value = code;
            t.value_length = 0;

            while(IS_NUMBER(*code)) {
                t.value_length++;
                code++;
            }

            //TokenArray_add(ta, &t);
            prev->next = &t;
            prev = &t;
        } else
        if(IS_LETTER(*code)) {
            t.name = NAME;
            t.value = code;
            t.value_length = 0;

            while(IS_LETTER(*code)) {
                t.value_length++;
                code++;
            }

            prev->next = &t;
            prev = &t;
        } else
        if(IS_OPERATOR(*code)) {
            t.name = OPERATOR;
            t.value = code;
            t.value_length = 1;

            prev->next = &t;
            prev = &t;
        } else
        if(IS_PAREN(*code)) {
            t.name = PAREN;
            t.value = code;
            t.value_length = 1;

            prev->next = &t;
            prev = &t;
        } else
        if(IS_QUOTE(*code)) {
            t.name = STRING;
            t.value = code;
            t.value_length = 0;

            while(!IS_QUOTE(*code)) {
                t.value_length++;
                code++;
            }

            prev->next = &t;
            prev = &t;
        } else
        if(IS_BRACE(*code)) {
            t.name = BRACE;
            t.value = code;
            t.value_length = 1;

            prev->next = &t;
            prev = &t;
        }
        if(IS_COLON(*code)) {
            t.name = COLON;
            t.value = code;
            t.value_length = 1;
            
            prev->next = &t;
            prev = &t;
        }
        else {
            // ignore
        }

        code++;
    }
}
