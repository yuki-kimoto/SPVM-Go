// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>

#include "spvm_native.h"
#include "uv.h"

static const char* FILE_NAME = "Go/UV.c";

int32_t SPVM__Go__UV__default_loop(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_loop_t* uv_loop = uv_default_loop();
  
  SPVM_OBJ* obj_uv_loop = env->new_pointer_object_by_name(env, stack, "Go::UV::Loop", uv_loop, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  stack[0].oval = obj_uv_loop;
  
  return 0;
}
