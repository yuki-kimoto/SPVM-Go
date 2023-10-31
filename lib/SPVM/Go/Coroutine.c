// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>

#include "spvm_native.h"
#include "coro.h"

static const char* FILE_NAME = "Go/Coroutine.c";

void coro_transfer_fix(void* from, void* to) {
  
  // TODO: coro_transfer have some errors, but this fflush call fix it. I don't understant the reason.
  fflush(stderr);
  
  coro_transfer(from, to);
}

static void coroutine_handler (void* obj_self) {
  
  int32_t error_id = 0;
  
  void** pointer_items = (void**)SPVM_NATIVE_GET_POINTER(obj_self);
  
  SPVM_ENV* env = pointer_items[2];
  
  SPVM_VALUE* stack = env->new_stack(env);
  
  env->set_field_object_by_name(env, stack, obj_self, "exception", NULL, &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  env->set_field_int_by_name(env, stack, obj_self, "error_id", 0, &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  void* obj_task = env->get_field_object_by_name(env, stack, obj_self, "task", &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  void* method = env->get_instance_method(env, stack, obj_task, "");
  
  stack[0].oval = obj_task;
  error_id = env->call_method(env, stack, method, 0);
  
  if (error_id) {
    
    void* obj_exception = env->get_exception(env, stack);
    const char* exception = env->get_chars(env, stack, obj_exception);
    
    env->set_field_object_by_name(env, stack, obj_self, "exception", obj_exception, &error_id, __func__, FILE_NAME, __LINE__);
    assert(error_id == 0);
    
    env->set_field_int_by_name(env, stack, obj_self, "error_id", error_id, &error_id, __func__, FILE_NAME, __LINE__);
    assert(error_id == 0);
    
    fprintf(env->api->runtime->get_spvm_stderr(env->runtime), "[An exception is converted to a warning at the end of a Go coroutine]\n");
    
    env->print_stderr(env, stack, obj_exception);
  }
  
  void* obj_return_back = env->get_field_object_by_name(env, stack, obj_self, "return_back", &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  coro_context* coroutine_context = pointer_items[0];
  
  void** coroutine_context_return_back_pointer_items = env->get_pointer(env, stack, obj_return_back);
  
  coro_context* coroutine_context_return_back = coroutine_context_return_back_pointer_items[0];
  assert(error_id == 0);
  
  env->set_field_byte_by_name(env, stack, obj_self, "finished", 1, &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  env->set_exception(env, stack, NULL);
  
  env->free_stack(env, stack);
  
  coro_transfer_fix(coroutine_context, coroutine_context_return_back);
  assert(0);
  
  return;
}

int32_t SPVM__Go__Coroutine__init_coroutine(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_task = env->get_field_object_by_name(env, stack, obj_self, "task", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  coro_context* coroutine_context = env->new_memory_block(env, stack, sizeof(coro_context));
  struct coro_stack* coroutine_stack = NULL;
  if (obj_task) {
    coroutine_stack = env->new_memory_block(env, stack, sizeof(struct coro_stack*));
    
    if (!coro_stack_alloc(coroutine_stack, 0)) {
      return env->die(env, stack, "coro_stack_alloc failed.", __func__, FILE_NAME, __LINE__);
    }
    
    coro_create(coroutine_context, coroutine_handler, obj_self, coroutine_stack->sptr,  coroutine_stack->ssze);
  }
  else {
    coro_create(coroutine_context, NULL, NULL, NULL, 0);
  }
  
  void** pointer_items = env->new_memory_block(env, stack, sizeof(void*) * 4);
  
  void* obj_spvm_stack = env->get_field_object_by_name(env, stack, obj_self, "stack", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SPVM_VALUE* spvm_stack = env->get_pointer(env, stack, obj_spvm_stack);
  
  pointer_items[0] = coroutine_context;
  pointer_items[1] = coroutine_stack;
  pointer_items[2] = env;
  
  env->set_pointer(env, stack, obj_self, pointer_items);
  
  return 0;
}

int32_t SPVM__Go__Coroutine__transfer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_coroutine_from = stack[0].oval;
  
  if (!obj_coroutine_from) {
    return env->die(env, stack, "$from must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void** coroutine_from_pointer_items = env->get_pointer(env, stack, obj_coroutine_from);
  
  coro_context* coroutine_context_from = coroutine_from_pointer_items[0];
  
  void* obj_coroutine_to = stack[1].oval;
  
  if (!obj_coroutine_to) {
    return env->die(env, stack, "$to must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void** coroutine_to_pointer_items = env->get_pointer(env, stack, obj_coroutine_to);
  
  coro_context* coroutine_context_to = coroutine_to_pointer_items[0];
  
  coro_transfer_fix(coroutine_context_from, coroutine_context_to);
  
}

int32_t SPVM__Go__Coroutine__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  void** pointer_items = env->get_pointer(env, stack, obj_self);
  
  coro_context* coroutine_context = pointer_items[0];
  
  struct coro_stack* coroutine_stack = pointer_items[1];
  
  if (coroutine_stack) {
    coro_stack_free(coroutine_stack);
  }
  
  coro_destroy(coroutine_context);
  
  env->free_memory_block(env, stack, coroutine_context);
  
  env->free_memory_block(env, stack, coroutine_stack);
  
  env->free_memory_block(env, stack, pointer_items);
  
}
