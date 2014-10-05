#include "minunit.h"
#include <lcthw/ringbuffer.h>
#include <lcthw/dbg.h>

#define NUM_TEST_DATA   4
#define AVAILABLE_SPACE 3 * 6

char* test_data[NUM_TEST_DATA] = {
  "test1",
  "test2",
  "test3",
  "test4"
};

static RingBuffer* buffer = NULL;

char* test_create()
{
  buffer = RingBuffer_create(AVAILABLE_SPACE);

  mu_assert(buffer != NULL, "Cannot create buffer.");
  mu_assert(RingBuffer_empty(buffer), "Buffer should be empty after creating.");

  return NULL;
}

char* test_destroy()
{
  mu_assert(buffer != NULL, "Buffer should be available when destroying.");
  RingBuffer_destroy(buffer);
 
  return NULL;
}

char* test_read_write()
{
  mu_assert(RingBuffer_available_space(buffer) == AVAILABLE_SPACE, 
            "Buffer should have enough space at the beginning.");

  mu_assert(RingBuffer_available_data(buffer) == 0, 
            "Buffer should have no available data yet.");

  // Writes.

  RingBuffer_write(buffer, test_data[0], 6);
  mu_assert(RingBuffer_available_data(buffer) == 6, "Available data value incorrect after write.");

  RingBuffer_write(buffer, test_data[1], 6);
  mu_assert(RingBuffer_available_data(buffer) == 12, "Available data value incorrect after write.");

  RingBuffer_write(buffer, test_data[2], 6);

  mu_assert(RingBuffer_available_space(buffer) == (AVAILABLE_SPACE - 18), 
            "Available space incorrect after series of writes.");

  mu_assert(RingBuffer_full(buffer), 
            "Buffer should be full at this moment.");

  // Reads.

  char target[6];
  
  RingBuffer_read(buffer, target, 6);
  mu_assert(strcmp(target, test_data[0]) == 0, "Invalid data read from ring buffer.");

  RingBuffer_read(buffer, target, 6);
  mu_assert(strcmp(target, test_data[1]) == 0, "Invalid data read from ring buffer.");

  // Overriding.

  RingBuffer_write(buffer, test_data[3], 6);
  RingBuffer_read(buffer, target, 6);
  mu_assert(strcmp(target, test_data[2]) == 0, "Invalid data read from ring buffer.");

  return NULL;
}

char* all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);
  mu_run_test(test_read_write);
  mu_run_test(test_destroy);
  
  return NULL;
}

RUN_TESTS(all_tests);
