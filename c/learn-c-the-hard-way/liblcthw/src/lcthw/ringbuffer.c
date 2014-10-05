#include <assert.h>
#include <stdlib.h>
#include <lcthw/dbg.h>
#include <lcthw/ringbuffer.h>

RingBuffer* RingBuffer_create(int length)
{
  RingBuffer* buffer = calloc(1, sizeof(RingBuffer));
  check_mem(buffer);

  buffer->length = length + 1;
  buffer->start = 0;
  buffer->end = 0;

  buffer->buffer = calloc(buffer->length, 1);
  check_mem(buffer->buffer);

  return buffer;

error:
  if (buffer) {
    free(buffer);
  }

  return NULL;
}

void RingBuffer_destroy(RingBuffer* buffer)
{
  if (buffer) {
    free(buffer->buffer);
    free(buffer);
  }
}

int RingBuffer_write(RingBuffer* buffer, char* data, int length)
{
  if (length > RingBuffer_available_space(buffer)) {
    return -1;
  }

  void* result = memcpy(buffer->buffer + buffer->end, data, length);
  check(result != NULL, "Failed to write into buffer.");

  RingBuffer_commit_write(buffer, length);

  if (buffer->end == buffer->start) {
    RingBuffer_commit_read(buffer, length);
  }

  return length;
  
error:
  return -1;
}

int RingBuffer_read(RingBuffer* buffer, char* target, int amount)
{
  if (amount > RingBuffer_available_data(buffer)) {
    debug("Available is: %d, amount: %d", RingBuffer_available_space(buffer), amount);
    return -1;
  }
  
  void* result = memcpy(target, buffer->buffer + buffer->start, amount);
  check(result != NULL, "Failed to read buffer to target.");

  RingBuffer_commit_read(buffer, amount);

  return amount;

error:
  return -1;
}

bstring RingBuffer_gets(RingBuffer *buffer, int amount)
{
  check(amount > 0, "Need more than 0 for gets, you gave: '%d'", amount);
  check_debug(amount <= RingBuffer_available_data(buffer), "Not enough in the buffer.");

  bstring result = blk2bstr(RingBuffer_starts_at(buffer), amount);
  
  check(result != NULL, "Failed to create gets result.");
  check(blength(result) == amount, "Wrong result length.");

  RingBuffer_commit_read(buffer, amount);
  assert(RingBuffer_available_data(buffer) >= 0 && "Error in read commit.");

  return result;

error:
  return NULL;
}
