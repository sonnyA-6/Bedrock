
#include <assert.h>
#include <stdio.h>
#include "stack.h"

void test_stack_init() {
    Stack s;
    int result = stack_init(&s);

    assert(result == 0);
    assert(s.top == -1);

    printf("test_stack_init passed\n");
}

void test_stack_push_and_peek() {
    Stack s;
    stack_init(&s);

    int value = 74;
    stack_push(&s, &value);

    int *peeked = (int *)stack_peek(&s);
    assert(*peeked == 74);

    printf("test_stack_push_and_peek passed\n");
}

void test_stack_pop() {
    Stack s;
    stack_init(&s);

    int value = 42;
    stack_push(&s, &value);

    int *popped = (int *)stack_pop(&s);
    assert(*popped == 42);
    assert(stack_is_empty(&s));

    printf("test_stack_pop passed\n");
}

void test_stack_is_empty() {
    Stack s;
    stack_init(&s);

    assert(stack_is_empty(&s));

    printf("test_stack_is_empty passed\n");
}

int main(void) {
    test_stack_init();
    test_stack_push_and_peek();
    test_stack_pop();
    test_stack_is_empty();

    printf("All tests passed\n");
    return 0;
}

