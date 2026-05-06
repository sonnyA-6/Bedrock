
#include "stack.h"
#include <stddef.h>
#include <string.h>

//Stack Functions
//Initialize Stack
int stack_init(Stack *s) {
    //Null Pointer Guard
    if (s == NULL) {
        return -1;
    }
    //Create a new stack with the caller provided array: s and initialize array values to zero.
    s->top = -1;
    memset(&s->stack_data, 0, sizeof(s->stack_data));
    return 0;
}
//Pushes data value to the "top" of the stack
int stack_push(Stack *stk, void *data) {
    //Null Pointer Guard
    if (stk == NULL || data == NULL || stack_is_full(stk)) {
        return -1;
    }
    //Push the data to the correct index, increment the position
    stk->top++;
    stk->stack_data[stk->top] = data;
    return 0;
}
//Pop the item at the top of the stack
void *stack_pop(Stack *stk) {
    //Null Pointer Guard
    if (stk == NULL || stack_is_empty(stk)) {
        return NULL;
    }
    void *popped_item = stk->stack_data[stk->top];
    stk->stack_data[stk->top] = NULL;
    stk->top--;
    return popped_item;
}
//Look at what item is at the top of the stack
void *stack_peek(const Stack *stk) {
    //Null Pointer Guard
    if (stk == NULL || stack_is_empty(stk)) {
        return NULL;
    }
    return stk->stack_data[stk->top];
}
//Check top variable to discern if stack is full
bool stack_is_full(const Stack *stk) {
    //Look at STACK_MAX_CAPACITY
    return stk->top == STACK_MAX_CAPACITY - 1;
}
//Check top value to discern if stack is empty
bool stack_is_empty(const Stack *stk) {
    //Look at sentinel value.
    return stk->top == -1;
}