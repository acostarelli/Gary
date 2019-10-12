#include "gary.h"
#include "compiler.h"

#include <stdio.h>
#include <string.h>


int main(void) {
    FILE *code_fp = fopen("./00test.gary", "r");
    char *code = load_file(code_fp);

    FILE *stdlib_fp = fopen("./garystdlib.asm", "r");
    char *stdlib = load_file(stdlib_fp);

    compile(code, stdout);

    return 0;
}
