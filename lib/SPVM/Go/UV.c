// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>

#include "spvm_native.h"
#include "uv.h"

static const char* FILE_NAME = "Go/UV.c";

void boot_Go__UV(void) {
  
}

static uv_loop_t* uv_loop = NULL;

int32_t SPVM__Go__UV__run_default(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  uv_loop_t* uv_loop = uv_default_loop();
  
  int32_t status = uv_run(uv_loop, UV_RUN_DEFAULT);
  
  if (!(status == 0)) {
    return env->die(env, stack, "[uv Error]uv_run failed. $mode=%d", __func__, FILE_NAME, __LINE__, UV_RUN_DEFAULT);
  }
  
  return 0;
}

int32_t SPVM__Go__UV__run_nowait(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  uv_loop_t* uv_loop = uv_default_loop();
  
  int32_t status = uv_run(uv_loop, UV_RUN_NOWAIT);
  
  if (!(status == 0)) {
    return env->die(env, stack, "[uv Error]uv_run failed. $mode=%d", __func__, FILE_NAME, __LINE__, UV_RUN_NOWAIT);
  }
  
  return 0;
}
