#include "gary.h"
#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_file_size(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return size;
}

char *load_file(FILE *fp) {
    size_t size = get_file_size(fp);
    char *content = malloc(size + 1);
    char *start = content;

    char c;
    while((c = getc(fp)) != EOF) {
        *content = c;

        content++;
    }

    *content = '\0';

    return start;
}

int uid() {
    static int id = 0;
    return id++;
}

void Stack_init(struct Stack *s) {
    s->length = 0;
}
void Stack_push(struct Stack *s, int n) {
    if(s->length == 32) {
        perror("Gary: stack size limit reached.");
        return;
    }

    s->data[s->length] = n;
    s->length++;
}
int Stack_pop(struct Stack *s) {
    s->length--;

    return s->data[s->length];
}


void DynStrArray_init(struct DynStrArray *dsa) {
    dsa->items = malloc(sizeof(char *));
    dsa->used = 0;
    dsa->size = 1;
}
void DynStrArray_add(struct DynStrArray *dsa, char *item) {
    if(dsa->used == dsa->size) {
        dsa->size = dsa->size * 2;
        dsa->items = realloc(dsa->items, dsa->size * sizeof(char *));
    }

    dsa->items[dsa->used] = malloc(strlen(item)+1); // \0

    memcpy(dsa->items[dsa->used], item, strlen(item)+1);
    dsa->used++;
}
bool DynStrArray_contains(struct DynStrArray *dsa, char *str) {
    for(int i = 0; i < dsa->used; i++) {
        char *cmp = dsa->items[i];
        if(strcmp(cmp, str) == 0) {
            return true;
        }
    }
    return false;
}