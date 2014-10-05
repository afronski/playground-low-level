#ifndef _lcthw_stack_h_
#define _lcthw_stack_h_

#include <lcthw/list.h>

typedef struct Stack {
  List* internal;
} Stack;

Stack* Stack_create();
void Stack_destroy(Stack* stack);

void* Stack_peek(Stack* stack);

size_t Stack_count(Stack* stack);

void Stack_push(Stack* stack, void* what);
void* Stack_pop(Stack* stack);

#define STACK_FOREACH(stack, cur)   LIST_FOREACH(stack->internal, first, next, cur)

#endif
