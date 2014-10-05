#include <stdlib.h>
#include <lcthw/stack.h>
#include <lcthw/dbg.h>

Stack* Stack_create()
{
  Stack* stack = calloc(1, sizeof(Stack));
  check_mem(stack);

  stack->internal = List_create();

  return stack;

error:
  return NULL;
}

void Stack_destroy(Stack* stack)
{
  if (stack) {
    List_destroy(stack->internal);
    free(stack);
  }
}

void* Stack_peek(Stack* stack)
{
  return List_last(stack->internal);
}

size_t Stack_count(Stack* stack)
{
  return List_count(stack->internal);
}

void Stack_push(Stack* stack, void* what)
{
  List_push(stack->internal, what);
}

void* Stack_pop(Stack* stack)
{
  return List_pop(stack->internal);
}
