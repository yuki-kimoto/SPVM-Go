// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "coro.h"

static const char* FILE_NAME = "Go/Goroutine.c";

int32_t SPVM__Go__Goroutine__test(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  /*
    void coro_create (coro_context *ctx,
                      coro_func coro,
                      void *arg,
                      void *sptr,
                      size_t ssze);
  */
  
  coro_context* coro_ctx = env->new_memory_block(env, stack, sizeof(coro_context));
  
  coro_create(coro_ctx, 0, 0, 0, 0);
  
  coro_destroy(coro_ctx);
  
  return 0;
}
