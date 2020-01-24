#include "gary.h"
#include "compiler.h"
#include "generator.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if(argc < 3) {
        printf("Use: %s [file.gary] [output.asm]\n", argv[0]);
        return 1;
    }

    FILE *code_fp = fopen(argv[1], "r");
    FILE *out_fp  = fopen(argv[2], "w");

    char *code = load_file(code_fp);
    compile(code, out_fp);

    return 0;
}