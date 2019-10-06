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
#define IS_COLON(c) (c == ':')

typedef enum {
    NUMBER,
    NAME,
    OPERATOR,
    PAREN,
    QUOTE,
    BRACE,
    STRING,
    COLON
} TokenType;

struct Token {
    TokenType name;
    char *value;
    int value_length;
};

struct TokenArray {
    struct Token *tokens;
    size_t used;
    size_t size;
};

void TokenArray_init(struct TokenArray *ta);

void TokenArray_add(struct TokenArray *ta, struct Token *t);

void TokenArray_clear(struct TokenArray *ta);

void tokenize(char *code, struct TokenArray *ta);

void TokenArray_print(struct TokenArray *ta);

void Token_print(struct Token *t);

#endif
