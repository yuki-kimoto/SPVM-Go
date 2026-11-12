// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>

#include "spvm_native.h"
#include "coro.h"

typedef struct {
  SPVM_ENV* env;
  SPVM_VALUE* stack;
  coro_context* st_coro_context;
  struct coro_stack* st_coro_stack;
  const char* caller_func_name;
  const char* caller_file;
  int32_t caller_line;
} SPVM__Go__Goroutine__CORO_DATA;

static const char* FILE_NAME = "Go/Goroutine.c";

static void SPVM__Go__Goroutine__coro_start_cb (void* data) {
  
  SPVM_OBJ* obj_self = (SPVM_OBJ*)data;
  
  int32_t error_id = 0;
  
  SPVM__Go__Goroutine__CORO_DATA* coro_data = SPVM_NATIVE_GET_POINTER(obj_self);
  
  SPVM_ENV* env = coro_data->env;
  
  SPVM_VALUE* stack = coro_data->stack;
  
  const char* caller_func_name = coro_data->caller_func_name;
  const char* caller_file = coro_data->caller_file;
  int32_t caller_line = coro_data->caller_line;
  
  SPVM_OBJ* obj_task = env->get_field_object_by_name(env, stack, obj_self, "task", &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  void* method = env->get_instance_method(env, stack, obj_task, "");
  
  stack[0].oval = obj_task;
  error_id = env->call_method(env, stack, method, 1, caller_func_name, caller_file, caller_line);
  
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
  
  SPVM_OBJ* obj_schedule_goroutine = env->get_field_object_by_name(env, stack, obj_self, "schedule_goroutine", &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  coro_context* st_coro_context = coro_data->st_coro_context;
  
  SPVM__Go__Goroutine__CORO_DATA* st_coro_context_schedule_goroutine_coro_data = env->get_pointer(env, stack, obj_schedule_goroutine);
  
  coro_context* st_coro_context_schedule_goroutine = st_coro_context_schedule_goroutine_coro_data->st_coro_context;
  assert(error_id == 0);
  
  env->set_field_byte_by_name(env, stack, obj_self, "finished", 1, &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  coro_transfer(st_coro_context, st_coro_context_schedule_goroutine);
  
  assert(0);
}

int32_t SPVM__Go__Goroutine__init_goroutine(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_self = stack[0].oval;
  
  SPVM_OBJ* obj_task = env->get_field_object_by_name(env, stack, obj_self, "task", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  coro_context* st_coro_context = env->new_memory_block(env, stack, sizeof(coro_context));
  struct coro_stack* st_coro_stack = NULL;
  if (obj_task) {
    st_coro_stack = env->new_memory_block(env, stack, sizeof(struct coro_stack));
    
    if (!coro_stack_alloc(st_coro_stack, 0)) {
      return env->die(env, stack, "coro_stack_alloc failed.", __func__, FILE_NAME, __LINE__);
    }
    
    coro_create(st_coro_context, SPVM__Go__Goroutine__coro_start_cb, obj_self, st_coro_stack->sptr,  st_coro_stack->ssze);
  }
  else {
    coro_create(st_coro_context, NULL, NULL, NULL, 0);
  }
  
  SPVM__Go__Goroutine__CORO_DATA* coro_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__Goroutine__CORO_DATA));
  
  coro_data->st_coro_context = st_coro_context;
  coro_data->st_coro_stack = st_coro_stack;
  coro_data->env = env;
  coro_data->stack = env->new_stack(env);
  
  SPVM_OBJ* obj_caller_info = env->get_field_object_by_name(env, stack, obj_self, "caller_info", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  SPVM_OBJ* obj_caller_method_abs_name = env->get_field_object_by_name(env, stack, obj_caller_info, "method_abs_name", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  const char* caller_method_abs_name = env->get_chars(env, stack, obj_caller_method_abs_name);
  coro_data->caller_func_name = caller_method_abs_name;
  
  SPVM_OBJ* obj_caller_file = env->get_field_object_by_name(env, stack, obj_caller_info, "file", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  const char* caller_file = env->get_chars(env, stack, obj_caller_file);
  coro_data->caller_file = caller_file;
  
  int32_t caller_line = env->get_field_int_by_name(env, stack, obj_caller_info, "line", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  coro_data->caller_line = caller_line;
  
  env->set_pointer(env, stack, obj_self, coro_data);
  
  return 0;
}

int32_t SPVM__Go__Goroutine__transfer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_goroutine_from = stack[0].oval;
  
  SPVM_OBJ* obj_goroutine_to = stack[1].oval;
  
  if (!obj_goroutine_from) {
    return env->die(env, stack, "$from must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  SPVM__Go__Goroutine__CORO_DATA* coro_data = env->get_pointer(env, stack, obj_goroutine_from);
  
  coro_context* st_coro_context_from = coro_data->st_coro_context;
  
  if (!obj_goroutine_to) {
    return env->die(env, stack, "$to must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  SPVM__Go__Goroutine__CORO_DATA* goroutine_to_coro_data = env->get_pointer(env, stack, obj_goroutine_to);
  
  coro_context* st_coro_context_to = goroutine_to_coro_data->st_coro_context;
  
  coro_transfer(st_coro_context_from, st_coro_context_to);
  
  return 0;
}

int32_t SPVM__Go__Goroutine__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_self = stack[0].oval;
  
  SPVM__Go__Goroutine__CORO_DATA* coro_data = env->get_pointer(env, stack, obj_self);
  
  coro_context* st_coro_context = coro_data->st_coro_context;
  
  struct coro_stack* st_coro_stack = coro_data->st_coro_stack;
  
  env->free_stack(env, coro_data->stack);
  
  if (st_coro_stack) {
    coro_destroy(st_coro_context);
    
    coro_stack_free(st_coro_stack);
    
    env->free_memory_block(env, stack, st_coro_stack);
  }
  
  env->free_memory_block(env, stack, st_coro_context);
  
  env->free_memory_block(env, stack, coro_data);
  
  return 0;
}
