// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "coro.h"

static const char* FILE_NAME = "Go/Goroutine.c";

static void goroutine_handler (void* arg) {
  
  void** args = (void**)arg;
  
  SPVM_ENV* env = args[0];
  SPVM_VALUE* goroutine_stack = args[1];
  void* obj_callback = args[2];
  
  int32_t error_id = 0;
  
  {
    env->call_instance_method_by_name(env, goroutine_stack, "", 0, &error_id, __func__, FILE_NAME, __LINE__);
    
    if (error_id) {
      void* obj_exception = env->get_exception(env, goroutine_stack);
      
      const char* exception = env->get_chars(env, goroutine_stack, obj_exception);
      
      spvm_warn("%s", exception);
    }
  }
  
  return;
}

int32_t SPVM__Go__Goroutine__new_beta(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_callback = stack[0].oval;
  
  if (!obj_callback) {
    return env->die(env, stack, "$callback must be defined.", __func__, FILE_NAME, __LINE__);
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
  
  SPVM_VALUE* goroutine_stack = env->new_stack(env);
  
  void** args[3] = {0};
  
  args[0] = (void*)env;
  args[1] = (void*)goroutine_stack;
  args[2] = obj_callback;
  
  struct coro_stack* coro_goroutine_stack = env->new_memory_block(env, stack, sizeof(struct coro_stack));
  
  coro_stack_alloc(coro_goroutine_stack, stack_size);
  
  coro_create(goroutine, goroutine_handler, (void*)args, coro_goroutine_stack->sptr, coro_goroutine_stack->ssze);
  
  coro_destroy(goroutine);
  
  env->free_stack(env, goroutine_stack);
  
  return 0;
}
