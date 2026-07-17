// Copyright (c) 2026 Yuki Kimoto
// MIT License

#include "spvm_native.h"
#include "uv.h"

static const char* FILE_NAME = "Go/UV/Loop.c";

int32_t SPVM__Go__UV__Loop__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_loop_t* loop = env->new_memory_block(env, stack, sizeof(uv_loop_t));
  
  uv_loop_init(loop);
  
  SPVM_OBJ* obj_self = env->new_pointer_object_by_name(env, stack, "Go::UV::Loop", loop, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  stack[0].oval = obj_self;

  return 0;
}

int32_t SPVM__Go__UV__Loop__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_self = stack[0].oval;
  
  uv_loop_t* loop = env->get_pointer(env, stack, obj_self);
  assert(loop);
  
  uv_loop_close(loop);
  
  env->free_memory_block(env, stack, loop);
  
  return 0;
}
