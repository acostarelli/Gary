#ifndef TOKENIZER
#define TOKENIZER

#include "gary.h"

#include <stdlib.h>

#define IS_NUMBER(c) (c >= '0' && c <= '9')
#define IS_LETTER(c) ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
#define IS_OPERATOR(c) (c == '+' || c == '-' || c == '*' || c == '/')
#define IS_PAREN(c) (c == '(' || c == ')')
#define IS_QUOTE(c) (c == '"')
#define IS_BRACE(c) (c == '{' || c == '}')

typedef enum {
    NUMBER,
    NAME,
    OPERATOR,
    PAREN,
    STRING,
    BRACE
} TokenType;

typedef struct {
    TokenType name;
    char *value;
    int value_length;
} Token;

typedef struct {
    Token *tokens;
    size_t used;
    size_t size;
} TokenArray;

void TokenArray_init(TokenArray *ta, size_t size);

void TokenArray_add(TokenArray *ta, Token *t);

void TokenArray_clear(TokenArray *ta);

void tokenize(char *code, TokenArray *ta);

#endif
