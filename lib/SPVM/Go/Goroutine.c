// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>

#include "spvm_native.h"
#include "coro.h"

static const char* FILE_NAME = "Go/Goroutine.c";

static void goroutine_handler (void* obj_self_tmp) {
  
  SPVM_OBJ* obj_self = obj_self_tmp;
  
  int32_t error_id = 0;
  
  void** pointer_items = (void**)SPVM_NATIVE_GET_POINTER(obj_self);
  
  SPVM_ENV* env = pointer_items[2];
  
  SPVM_VALUE* stack = pointer_items[3];
  
  SPVM_OBJ* obj_task = env->get_field_object_by_name(env, stack, obj_self, "task", &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  void* method = env->get_instance_method(env, stack, obj_task, "");
  
  stack[0].oval = obj_task;
  error_id = env->call_method(env, stack, method, 1, __func__, FILE_NAME, __LINE__);
  
  if (error_id) {
    // Reconstruct the full exception message including stack trace.
    // The level 0 means the trace starts from the origin of the exception.
    
    int32_t scope_id = env->enter_scope(env, stack);
    
    SPVM_OBJ* obj_full_exception_message = env->build_exception_message(env, stack, 0);
    
    fprintf(env->api->runtime->get_spvm_stderr(env->runtime), "[An exception thrown in a goroutine is converted to a warning]\n");
    
    // Print the full exception message with stack trace.
    env->print_stderr(env, stack, obj_full_exception_message);
    
    env->leave_scope(env, stack, scope_id);
    
    fprintf(env->api->runtime->get_spvm_stderr(env->runtime), "\n");
  }
  
  SPVM_OBJ* obj_return_back = env->get_field_object_by_name(env, stack, obj_self, "return_back", &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  coro_context* goroutine_context = pointer_items[0];
  
  void** goroutine_context_return_back_pointer_items = env->get_pointer(env, stack, obj_return_back);
  
  coro_context* goroutine_context_return_back = goroutine_context_return_back_pointer_items[0];
  assert(error_id == 0);
  
  env->set_field_byte_by_name(env, stack, obj_self, "finished", 1, &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  coro_transfer(goroutine_context, goroutine_context_return_back);
  
  assert(0);
}

int32_t SPVM__Go__Goroutine__init_goroutine(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_self = stack[0].oval;
  
  SPVM_OBJ* obj_task = env->get_field_object_by_name(env, stack, obj_self, "task", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  coro_context* goroutine_context = env->new_memory_block(env, stack, sizeof(coro_context));
  struct coro_stack* goroutine_stack = NULL;
  if (obj_task) {
    goroutine_stack = env->new_memory_block(env, stack, sizeof(struct coro_stack));
    
    if (!coro_stack_alloc(goroutine_stack, 0)) {
      return env->die(env, stack, "coro_stack_alloc failed.", __func__, FILE_NAME, __LINE__);
    }
    
    coro_create(goroutine_context, goroutine_handler, obj_self, goroutine_stack->sptr,  goroutine_stack->ssze);
  }
  else {
    coro_create(goroutine_context, NULL, NULL, NULL, 0);
  }
  
  void** pointer_items = env->new_memory_block(env, stack, sizeof(void*) * 4);
  
  SPVM_VALUE* goroutine_spvm_stack = env->new_stack(env);
  
  pointer_items[0] = goroutine_context;
  pointer_items[1] = goroutine_stack;
  pointer_items[2] = env;
  pointer_items[3] = goroutine_spvm_stack;
  
  env->set_pointer(env, stack, obj_self, pointer_items);
  
  return 0;
}

int32_t SPVM__Go__Goroutine__transfer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_goroutine_from = stack[0].oval;
  
  if (!obj_goroutine_from) {
    return env->die(env, stack, "$from must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void** goroutine_from_pointer_items = env->get_pointer(env, stack, obj_goroutine_from);
  
  coro_context* goroutine_context_from = goroutine_from_pointer_items[0];
  
  SPVM_OBJ* obj_goroutine_to = stack[1].oval;
  
  if (!obj_goroutine_to) {
    return env->die(env, stack, "$to must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void** goroutine_to_pointer_items = env->get_pointer(env, stack, obj_goroutine_to);
  
  coro_context* goroutine_context_to = goroutine_to_pointer_items[0];
  
  coro_transfer(goroutine_context_from, goroutine_context_to);
  
  return 0;
}

int32_t SPVM__Go__Goroutine__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_self = stack[0].oval;
  
  void** pointer_items = env->get_pointer(env, stack, obj_self);
  
  coro_context* goroutine_context = pointer_items[0];
  
  struct coro_stack* goroutine_stack = pointer_items[1];
  
  SPVM_VALUE* goroutine_spvm_stack = pointer_items[3];
  
  env->free_stack(env, goroutine_spvm_stack);
  
  if (goroutine_stack) {
    coro_destroy(goroutine_context);
    
    coro_stack_free(goroutine_stack);
    
    env->free_memory_block(env, stack, goroutine_stack);
  }
  
  env->free_memory_block(env, stack, goroutine_context);
  
  env->free_memory_block(env, stack, pointer_items);
  
  return 0;
}
