// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "Go/Goroutine/Argument.c";

int32_t SPVM__Go__Goroutine__Argument__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_gourotine_stack = stack[0].oval;
  
  SPVM_VALUE* goroutine_stack = env->get_pointer(env, stack, obj_gourotine_stack);
  
  void* obj_callback = stack[1].oval;
  
  void** arguments = env->new_memory_block(env, stack, sizeof(void*) * 3);
  
  arguments[0] = env;
  arguments[1] = goroutine_stack;
  arguments[2] = obj_callback;
  
  void* obj_self = env->new_pointer_object_by_name(env, stack, "Go::Goroutine::Argument", arguments, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_self;
  
  return 0;
}

int32_t SPVM__Go__Goroutine__Argument__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  void** arguments = env->get_pointer(env, stack, obj_self);
  
  env->free_memory_block(env, stack, arguments);
  
  return 0;
}

