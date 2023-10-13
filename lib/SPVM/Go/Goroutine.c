// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "coro.h"

static const char* FILE_NAME = "Go/Goroutine.c";

static void goroutine_handler (void* obj_self) {
  
  int32_t error_id = 0;
  
  void** pointer_items = (void**)SPVM_NATIVE_GET_POINTER(obj_self);
  
  SPVM_ENV* env = pointer_items[1];
  
  SPVM_VALUE* goroutine_stack = env->new_stack(env);
  
  void* obj_callback = env->get_field_object_by_name(env, goroutine_stack, obj_self, "callback", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    void* obj_exception = env->get_exception(env, goroutine_stack);
    
    const char* exception = env->get_chars(env, goroutine_stack, obj_exception);
    
    spvm_warn("%s", exception);
  }
  
  goroutine_stack[0].oval = obj_callback;
  env->call_instance_method_by_name(env, goroutine_stack, "", 0, &error_id, __func__, FILE_NAME, __LINE__);
  
  if (error_id) {
    void* obj_exception = env->get_exception(env, goroutine_stack);
    
    const char* exception = env->get_chars(env, goroutine_stack, obj_exception);
    
    spvm_warn("%s", exception);
  }
  
  return;
}

int32_t SPVM__Go__Goroutine__init_goroutine(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
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
  
  coro_context* goroutine = env->new_memory_block(env, stack, sizeof(coro_context));
  
  coro_create(goroutine, goroutine_handler, obj_self, coro_goroutine_stack->sptr, coro_goroutine_stack->ssze);
  
  void** pointer_items = env->new_memory_block(env, stack, sizeof(void*) * 3);
  
  pointer_items[0] = goroutine;
  pointer_items[1] = env;
  
  env->set_pointer(env, stack, obj_self, pointer_items);
  
  return 0;
}

int32_t SPVM__Go__Goroutine__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  void** pointer_items = env->get_pointer(env, stack, obj_self);
  
  coro_context* goroutine = pointer_items[0];
  
  coro_destroy(goroutine);
  
  env->free_memory_block(env, stack, goroutine);
  
  env->free_memory_block(env, stack, pointer_items);
  
}
