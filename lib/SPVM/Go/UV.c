// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>

#include "spvm_native.h"
#include "uv.h"

static const char* FILE_NAME = "Go/UV.c";

int32_t SPVM__Go__UV__strerror(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int32_t status = stack[0].ival;
  
  char uv_strerror[512];
  uv_strerror_r(status, uv_strerror, sizeof(uv_strerror));
  
  SPVM_OBJ* obj_uv_strerror = env->new_string_nolen(env, stack, uv_strerror);
  
  stack[0].oval = obj_uv_strerror;
  
  return 0;
}

