#include "duktape.h"

int adder(duk_context *ctx) {
  int i;
  int n = duk_get_top(ctx);

  double res = 0.0;

  for (i = 0; i < n; i++) {
    res += duk_to_number(ctx, i);
  }

  duk_push_number(ctx, res);

  return 1;
}

int main(int argc, char *argv[]) {
  (void) argc;
  (void) argv;

  duk_context *ctx = duk_create_heap_default();

  duk_eval_string(ctx, "print('Hello world!');");

  duk_push_global_object(ctx);
  duk_push_c_function(ctx, adder, DUK_VARARGS);
  duk_put_prop_string(ctx, -2, "adder");
  duk_pop(ctx);

  duk_eval_string(ctx, "print('2+3=' + adder(2, 3));");
  duk_pop(ctx);

  duk_destroy_heap(ctx);

  return 0;
}