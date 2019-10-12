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
#define IS_WHITESPACE(c) (c == ' ' || c == '\n')

/*typedef enum {
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
};*/

/**
 * LITERAL -> a name or an actual value (string, number)
 * EXPRESSION -> anything involving a series of expressions
 * and literals with some sort of operation being done.
 */
enum TokenType {
    LITERAL,
    EXPRESSION
};

/**
 * The actual token value exists between
 *      *value --> *(value + value_length - 1)
 *
 * The depth is an indicator for grouping whichever
 * Tokens go together under an expression. For example,
 * a math expression at depth 0 is going to have
 * two Tokens at depth 1: the operand Tokens.
 */
struct Token {
    enum TokenType type;
    char *value;
    int value_length;
    int depth;
};

/*struct Handler {
    int (*recognizer)(char *);
    void (*generator)(struct Token*);
}*/

struct TokenArray {
    struct Token *tokens;
    size_t used;
    size_t size;
};

struct Token TokenArray_pop(struct TokenArray *ta);

void TokenArray_init(struct TokenArray *ta);

void TokenArray_add(struct TokenArray *ta, struct Token *t);

void TokenArray_clear(struct TokenArray *ta);

void tokenize(char *code, struct TokenArray *ta);

void TokenArray_print(struct TokenArray *ta);

void Token_print(struct Token *t);

#endif
