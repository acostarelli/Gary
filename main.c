#include <stdio.h>
#include <string.h>

#include "gary.h"
#include "tokenizer.h"
#include "generator.h"

int main(int argc, char **argv) {
    FILE *fp = fopen("./00test.gary", "r");

    char *code = load_file(fp);

    struct TokenArray ta;
    TokenArray_init(&ta);

    tokenize(code, &ta);

    TokenArray_print(&ta);

    //printf("%d \n", prog.nodes[2].token->value_length);
    

    return 0;
}
