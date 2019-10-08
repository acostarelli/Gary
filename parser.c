#include "gary.h"
#include "parser.h"

#include <string.h>

/**
 * When calling this, pass the top most node and token;
 */
void generate_ast(struct ASTNodeArray *na, struct TokenArray *ta) {
    for(int i = 0; i < ta->used; i++) {
        struct Token *token = &ta->tokens[i];

        walk_ast(na, token, ta, i);
    }
}

void walk_ast(struct ASTNodeArray *na, struct Token *token, struct TokenArray *ta, int i) {
    struct ASTNode n;

    switch(token->name) {
        case NAME: {
            n.token = token;

            ASTNodeArray_add(na, &n);
            break;
        }
        case OPERATOR: {
            n.token = token;

            ASTNodeArray_add(na, &n);
            break;
        }
        case PAREN: {
            if(*token->value != ')') {
                token = &ta->tokens[++i];
                ASTNodeArray_init(&n.inner);
                walk_ast(&n.inner, token, ta, i);
            }
            break;
        }
        case NUMBER: {
            n.token = token;

            ASTNodeArray_add(na, &n);
            break;
        }
        case STRING: {
            n.token = token;

            ASTNodeArray_add(na, &n);
            break;
        }
        case BRACE: {
            puts("lower level created here");
            if(*token->value != '}') {
                puts("its the opener");
                token = &ta->tokens[++i];
                ASTNodeArray_init(&n.inner);
                walk_ast(&n.inner, token, ta, i);
                n.token->value_length = 0;
            }

            //n.token = NULL;
            break;
        }
        case COLON: {
            n.token = token;

            ASTNodeArray_add(na, &n);
            break;
        }
        case QUOTE: {
            n.token = token;

            ASTNodeArray_add(na, &n);
            break;
        }
    }
}

void ASTNodeArray_init(struct ASTNodeArray *na) {
    na->nodes = malloc(1 * sizeof(struct ASTNode));
    na->used = 0;
    na->size = 1;
}

void ASTNodeArray_add(struct ASTNodeArray *na, struct ASTNode *n) {
    if(na->used == na->size) {
        na->size = na->size * 2;
        na->nodes = realloc(na->nodes, na->size * sizeof(struct ASTNode));
    }

    na->nodes[na->used++] = *n;
}

void ASTNodeArray_clear(struct ASTNodeArray *na) {
    free(na->nodes);
    na->nodes = NULL;

    na->used = 0;
    na->size = 0;
}

void ASTNode_print(struct ASTNode *node) {
    puts("we made it back y'all");
    if(node->token->value_length != 0) { // this line doesn't work with nested AST nodes
        puts("good so far?");
        Token_print(node->token); 
        return;
    }
    puts("Entering lower level");
    ASTNodeArray_print(&node->inner);
}

void ASTNodeArray_print(struct ASTNodeArray *na) {
    puts("we in here");
    for(int i = 0; i < na->used; i++) {
        printf("%d: ", i);
        puts("uh oh");
        ASTNode_print(&na->nodes[i]);
        puts("we got here");
        printf("\n");
    }
    puts("Exiting lower level");
}
