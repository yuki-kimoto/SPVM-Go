// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "coro.h"

static const char* FILE_NAME = "Go/Goroutine.c";

static void goroutine_handler (void* obj_self) {
  
  int32_t error_id = 0;
  
  void** pointer_items = (void**)SPVM_NATIVE_GET_POINTER(obj_self);
  
  SPVM_ENV* env = pointer_items[2];
  
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
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_callback = env->get_field_object_by_name(env, stack, obj_self, "callback", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  coro_context* goroutine_context = env->new_memory_block(env, stack, sizeof(coro_context));
  struct coro_stack* goroutine_stack = NULL;
  if (obj_callback) {
    int32_t goroutine_stack_size = 512 * sizeof(void*);
    goroutine_stack = env->new_memory_block(env, stack, goroutine_stack_size);
    
    coro_create(goroutine_context, goroutine_handler, obj_self, goroutine_stack, goroutine_stack_size);
  }
  else {
    coro_create(goroutine_context, NULL, NULL, NULL, 0);
  }
  
  void** pointer_items = env->new_memory_block(env, stack, sizeof(void*) * 3);
    
  pointer_items[0] = goroutine_context;
  pointer_items[1] = goroutine_stack;
  pointer_items[2] = env;
  
  env->set_pointer(env, stack, obj_self, pointer_items);
  
  return 0;
}

int32_t SPVM__Go__Goroutine__transfer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_goroutine_from = stack[0].oval;
  
  void** goroutine_from_pointer_items = env->get_pointer(env, stack, obj_goroutine_from);
  
  coro_context* goroutine_from_goroutine_context = goroutine_from_pointer_items[0];
  
  void* obj_goroutine_to = stack[1].oval;
  
  void** goroutine_to_pointer_items = env->get_pointer(env, stack, obj_goroutine_to);
  
  coro_context* goroutine_to_goroutine_context = goroutine_to_pointer_items[0];
  
  coro_transfer(goroutine_from_goroutine_context, goroutine_to_goroutine_context);
}

int32_t SPVM__Go__Goroutine__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  void** pointer_items = env->get_pointer(env, stack, obj_self);
  
  coro_context* goroutine_context = pointer_items[0];
  
  struct coro_stack* goroutine_stack = pointer_items[1];
  
  coro_destroy(goroutine_context);
  
  env->free_memory_block(env, stack, goroutine_context);
  
  env->free_memory_block(env, stack, goroutine_stack);
  
  env->free_memory_block(env, stack, pointer_items);
  
}
