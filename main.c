#include "gary.h"
#include "compiler.h"
#include "generator.h"

#include <stdio.h>
#include <string.h>


int main(void) {
    FILE *code_fp = fopen("./00test.gary", "r");
    char *code = load_file(code_fp);

    compile(code, stdout);

    return 0;
}
