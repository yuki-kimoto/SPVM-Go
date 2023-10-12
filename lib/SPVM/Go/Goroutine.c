// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "coro.h"

static const char* FILE_NAME = "Go/Goroutine.c";

static void goroutine_handler (void* obj_goroutine_argument) {
  
  int32_t error_id = 0;
  
  void** goroutine_argument = (void**)SPVM_NATIVE_GET_POINTER(obj_goroutine_argument);
  
  SPVM_ENV* env = goroutine_argument[0];
  
  SPVM_VALUE* goroutine_stack = goroutine_argument[1];
  
  void* obj_callback = goroutine_argument[2];
  
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

int32_t SPVM__Go__Goroutine__init_goroutine(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  void* obj_goroutine_argument = stack[1].oval;
  
  coro_context* goroutine = env->new_memory_block(env, stack, sizeof(coro_context));
  
  struct coro_stack* coro_goroutine_stack = env->new_memory_block(env, stack, sizeof(struct coro_stack));
  
  int32_t stack_size;
  if (sizeof(SPVM_VALUE) > sizeof(void*)) {
    stack_size = 512 * sizeof(void*) * 2;
  }
  else {
    stack_size = 512 * sizeof(void*);
  }
  
  coro_stack_alloc(coro_goroutine_stack, stack_size);
  
  /*
    void coro_create (coro_context *ctx,
                      coro_func coro,
                      void *arg,
                      void *sptr,
                      size_t ssze);
  */
  
  coro_create(goroutine, goroutine_handler, obj_goroutine_argument, coro_goroutine_stack->sptr, coro_goroutine_stack->ssze);
  
  env->set_pointer(env, stack, obj_self, goroutine);
  
  return 0;
}

int32_t SPVM__Go__Goroutine__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  coro_context* goroutine = env->get_pointer(env, stack, obj_self);
  
  coro_destroy(goroutine);
}
