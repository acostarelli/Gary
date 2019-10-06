#ifndef PARSER
#define PARSER

#include "gary.h"

/* Parameters could be a linked list */
typedef enum {
    NumberLiteral,
    StringLiteral,
    CallExpression,
    DefinitionExpression
} ASTNodeType;

/**
 * token --> the data
 * next --> sequentially the next node
 * inner --> the start of an inner of ASTNodes
 */
/*struct ASTNode {
    struct Token *token;
    struct ASTNode *next;
    struct ASTNode *inner;
};*/


struct ASTNodeArray {
    struct ASTNode *nodes;
    size_t used;
    size_t size;
};

void ASTNodeArray_init(struct ASTNodeArray *ta);

void ASTNodeArray_add(struct ASTNodeArray *ta, struct ASTNode *n);

void ASTNodeArray_clear(struct ASTNodeArray *ta);

void ASTNode_print(struct ASTNode *node);

void ASTNodeArray_print(struct ASTNodeArray *na);

struct ASTNode {
    struct Token *token; // used for literals
    struct ASTNodeArray inner; // used for expressions
    // bruh shouldn't this ^ be a pointer? i can't get it to work that way tho
};

void generate_ast(struct ASTNodeArray *na, struct TokenArray *ta);

void walk_ast(struct ASTNodeArray *na, struct Token *token, struct TokenArray *ta, int i);

#endif
