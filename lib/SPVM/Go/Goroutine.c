// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "coro.h"

static const char* FILE_NAME = "Go/Goroutine.c";

int32_t SPVM__Go__Goroutine__new_beta(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* cb = stack[0].oval;
  
  if (!cb) {
    return env->die(env, stack, "$cb must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  /*
    void coro_create (coro_context *ctx,
                      coro_func coro,
                      void *arg,
                      void *sptr,
                      size_t ssze);
  */
  
  coro_context* goroutine = env->new_memory_block(env, stack, sizeof(coro_context));
  
  int32_t stack_size = sizeof(SPVM_VALUE) * 512;
  
  coro_create(goroutine, 0, cb, stack, stack_size);
  
  coro_destroy(goroutine);
  
  return 0;
}
