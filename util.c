#include "gary.h"

#include <stdio.h>

int get_file_size(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return size;
}

char *load_file(FILE *fp) {
    char *content = malloc(get_file_size(fp));
    char *start = content;

    char c;
    while((c = getc(fp)) != EOF) {
        *content = c;

        content++;
    }

    return start;
}
