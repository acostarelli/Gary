#ifndef COMPILER
#define COMPILER

void compile(char *c, FILE *out);

char *print_compiled(char *c, FILE *out);

struct Stack {
    int data[32];
    int length;
};

void Stack_init(struct Stack *s);

void Stack_push(struct Stack *s, int n);

int Stack_pop(struct Stack *s);

#endif
