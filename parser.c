#include "gary.h"
#include "parser.h"

#include <string.h>

/**
 * When calling this, pass the top most node and token;
 */
void walk_ast(ASTNode *n, Token *t, int i) {
    switch(t->name) {
        case NAME: {
            ASTNode node;

            char *value = malloc(t.value_length);
            memcpy(value, t.value, t.value_length);

            break;
        }
        case OPERATOR:


            break;
        case PAREN:
            break;
        
        /* There's gotta be a simpler way to do this. */
        case NUMBER: {
            node.type = NumberLiteral;
            node.value = t.value;
            node.value_length = t.value_length;

            break;
        }
        case STRING: {
            node.type = StringLiteral;
            node.value = t.value;
            node.value_length = t.value_length;

            break;
        }
        case BRACE:
            break;
        
        case COLON: {
            node.type = DefinitionExpression;
            node.value = last.value;

            break;
        }
    }

    last = t;
}

void walk_ast(ASTNode *ast) {

}
