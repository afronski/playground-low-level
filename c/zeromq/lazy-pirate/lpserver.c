// Lazy Pirate server
// Binds REQ socket to tcp://*:5555
// Like hwserver except:
//  - echoes request as-is.
//  - randomly runs slowly, or exits to simulate a crash.

#include <zhelpers.h>

int main(void)
{
  srandom((unsigned)time(NULL));

  void* context = zmq_ctx_new();
  void* server = zmq_socket(context, ZMQ_REP);

  zmq_bind(server, "tcp://*:5555");

  int cycles = 0;
  while (1) {
    char* request = s_recv(server);
    ++cycles;

    // Simulate various problems after a few cycles.
    if (cycles > 3 && randof(3) == 0) {
      printf("I: simulating a crash\n");
      break;
    } else if (cycles > 3 && randof(3) == 0) {
      printf("I: simulating CPU overload\n");
      sleep(2);
    }

    printf("I: normal request (%s)\n", request);

    // Do some "heavy work".
    sleep(1);

    s_send(server, request);
    free(request);
  }

  zmq_close(server);
  zmq_ctx_destroy(context);

  return 0;
}