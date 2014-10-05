#include <stdlib.h>
#include <lcthw/queue.h>
#include <lcthw/dbg.h>

Queue* Queue_create()
{
  Queue* queue = calloc(1, sizeof(Queue));
  check_mem(queue);

  queue->internal = List_create();

  return queue;

error:
  return NULL;
}

void Queue_destroy(Queue* queue)
{
  if (queue) {
    List_destroy(queue->internal);
    free(queue);
  }
}

void* Queue_peek(Queue* queue)
{
  return List_first(queue->internal);
}

size_t Queue_count(Queue* queue)
{
  return List_count(queue->internal);
}

void Queue_send(Queue* queue, void* what)
{
  List_push(queue->internal, what);
}

void* Queue_recv(Queue* queue)
{
  return List_shift(queue->internal);
}
