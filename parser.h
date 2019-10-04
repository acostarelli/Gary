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
typedef struct {
    struct Token *token;
    struct ASTNode *next;
    struct ASTNode *inner;
} ASTNode;

#endif
