#ifndef COMPILER
#define COMPILER

#include "gary.h"

#include <stdio.h>
#include <stdbool.h>

/**
 * Given a pointer to the Gary code c, simultaenously generates and prints
 * assembly code to out.
 */
void compile(char *c, FILE *out);

/**
 * The routine for compiling needs to use recursion for function definitions.
 * compile() calls this function, and then this function calls itself
 * for function definitions.
 *
 * This function is not called for every character, however. Inside the function
 * is a loop which iterates over every character. The point of using
 * recursion for function definitions is so that, after the inner function
 * code has been generated, additional necessary assembly can be generated
 * as found in the switch statement under the '{' case.
 *
 * A pointer to the pointer to the code is passed so that this function
 * can pass this double pointer to tokenizing subroutines (such as read_token).
 * These subroutines can then directly modify the pointer to the code by
 * changing *c, which means this function doesn't have to keep track of how
 * many characters to skip when a token is read, and the tokenizing functions
 * can skip ahead as they need.
 *
 * subid is for keepnig track of scope in the generated assembly code. When
 * a function is created in Gary, all of the generated labels inside the function
 * gets a specific subid (short for subroutine id). What this allows for is
 * variables with the same name to exist in different scopes. A variable named
 * apple in the base scope gets __sub0_apple . Then, a variable named apple
 * inside the a function gets __sub1_apple. This way, both variables can be
 * accessed separately.
 */
void print_compiled(char **c, int sub_id, struct Stack, struct DynStrArray, FILE *out);

/**
 * This r
 */
void skip_until(char **c, bool (*condition)(char));

#endif