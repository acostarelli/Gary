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
    STRING,
    BRACE,
    COLON
} TokenType;

typedef struct {
    TokenType name;
    char *value;
    int value_length;
    struct Token *next;
} Token;

#endif
