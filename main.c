#include <stdio.h>

#include "gary.h"
#include "tokenizer.h"

int main(int argc, char **argv) {
    FILE *fp = fopen("./00test.gary", "r");

    char *code = load_file(fp);
    
    TokenArray ta;
    TokenArray_init(&ta, 10);
    tokenize(code, &ta);

    return 0;
}
