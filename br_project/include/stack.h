
#ifndef BEDROCK_STACK_H
#define BEDROCK_STACK_H
#include <stdint.h>
#include <stdbool.h>
#define STACK_MAX_CAPACITY 64
//top holds a sentinel value of -1.
typedef struct {
    int32_t top;
    void *stack_data[STACK_MAX_CAPACITY];
} Stack;

//Stack Functions
int stack_init(Stack *s);
int stack_push(Stack *stk, void *data);
void *stack_pop(Stack *stk);
void *stack_peek(const Stack *stk);
bool stack_is_full(const Stack *stk);
bool stack_is_empty(const Stack *stk);

#endif //BEDROCK_STACK_H
