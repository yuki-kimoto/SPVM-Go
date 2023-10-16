// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "coro.h"

static const char* FILE_NAME = "Go/Goroutine.c";

void coro_transfer_tmp(void* from, void* to) {
  
  // TODO: coro_transfer have some errors, but this fflush call fix it. I don't understant the reason.
  fflush(stderr);
  
  coro_transfer(from, to);
}

static void goroutine_handler (void* obj_self) {
  
  int32_t error_id = 0;
  
  void** pointer_items = (void**)SPVM_NATIVE_GET_POINTER(obj_self);
  
  SPVM_ENV* env = pointer_items[2];
  
  SPVM_VALUE* stack = env->new_stack(env);
  
  void* obj_callback = env->get_field_object_by_name(env, stack, obj_self, "callback", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    void* obj_exception = env->get_exception(env, stack);
    
    const char* exception = env->get_chars(env, stack, obj_exception);
    
    spvm_warn("%s", exception);
  }
  
  void* method = env->get_instance_method(env, stack, obj_callback, "");
  
  stack[0].oval = obj_callback;
  error_id = env->call_method(env, stack, method, 0);
  
  if (error_id) {
    void* obj_exception = env->get_exception(env, stack);
    
    const char* exception = env->get_chars(env, stack, obj_exception);
    
    spvm_warn("%s", exception);
    
  }
  
  void* obj_return_back = env->get_field_object_by_name(env, stack, obj_self, "return_back", &error_id, __func__, FILE_NAME, __LINE__);
  
  if (error_id) {
  
    void* obj_exception = env->get_exception(env, stack);
    
    const char* exception = env->get_chars(env, stack, obj_exception);
    
    spvm_warn("%s", exception);
  }
  
  coro_context* goroutine_context = pointer_items[0];
  
  void** goroutine_context_return_back_pointer_items = env->get_pointer(env, stack, obj_return_back);
  
  coro_context* goroutine_context_return_back = goroutine_context_return_back_pointer_items[0];
  
  coro_transfer_tmp(goroutine_context, goroutine_context_return_back);
  
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
    int32_t goroutine_stack_size = 1000 * sizeof(void*);
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
  
  if (!obj_goroutine_from) {
    return env->die(env, stack, "$from must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void** goroutine_from_pointer_items = env->get_pointer(env, stack, obj_goroutine_from);
  
  coro_context* goroutine_context_from = goroutine_from_pointer_items[0];
  
  void* obj_goroutine_to = stack[1].oval;
  
  if (!obj_goroutine_to) {
    return env->die(env, stack, "$to must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void** goroutine_to_pointer_items = env->get_pointer(env, stack, obj_goroutine_to);
  
  coro_context* goroutine_context_to = goroutine_to_pointer_items[0];
  
  coro_transfer_tmp(goroutine_context_from, goroutine_context_to);
  
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
