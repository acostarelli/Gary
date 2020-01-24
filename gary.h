#ifndef GARY
#define GARY

#include <stdio.h>
#include <stdbool.h>

int get_file_size(FILE *fp);

char *load_file(FILE *fp);

int uid();

void stringcpy(char *dst, char *src, size_t size);

struct Stack {
    int data[32];
    int length;
};
void Stack_init(struct Stack *s);
void Stack_push(struct Stack *s, int n);
int Stack_pop(struct Stack *s);

struct DynStrArray {
    char **items;
    size_t used;
    size_t size;
};
void DynStrArray_init(struct DynStrArray *dsa);
void DynStrArray_add(struct DynStrArray *dsa, char *item);
bool DynStrArray_contains(struct DynStrArray *dsa, char *str);

#endif