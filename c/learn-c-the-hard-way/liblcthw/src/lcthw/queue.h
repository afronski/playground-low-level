#ifndef _lcthw_queue_h_
#define _lcthw_queue_h_

#include <lcthw/list.h>

typedef struct Queue {
  List* internal;
} Queue;

Queue* Queue_create();
void Queue_destroy(Queue* queue);

void* Queue_peek(Queue* queue);

size_t Queue_count(Queue* queue);

void Queue_send(Queue* queue, void* what);
void* Queue_recv(Queue* queue);

#define QUEUE_FOREACH(queue, cur)   LIST_FOREACH(queue->internal, first, next, cur)

#endif
