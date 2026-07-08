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

typedef struct {
  SPVM_ENV* env;
  SPVM_VALUE* stack;
  SPVM_OBJ* obj_uv;
  SPVM_OBJ* obj_goroutine;
} SPVM__Go__UV__HANDLE_DATA;

static void on_close_callback(uv_handle_t* handle) {
  SPVM__Go__UV__HANDLE_DATA* handle_data = (SPVM__Go__UV__HANDLE_DATA*)handle->data;
  
  SPVM_ENV* env = handle_data->env;
  SPVM_VALUE* stack = handle_data->stack;
  
  handle_data->env->free_memory_block(env, stack, handle_data);
  handle_data->env->free_memory_block(env, stack, handle);
}

static void on_timer_callback(uv_timer_t* handle) {
  uv_close((uv_handle_t*)handle, on_close_callback);
}

int32_t SPVM__Go__UV__timer(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  SPVM_OBJ* obj_self = stack[0].oval;
  SPVM_OBJ* obj_goroutine = stack[1].oval;
  
  uv_timer_t* timer_handle = env->new_memory_block(env, stack, sizeof(uv_timer_t));
  uv_timer_init(uv_loop, timer_handle);
  
  SPVM__Go__UV__HANDLE_DATA* handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
  handle_data->env = env;
  handle_data->stack = stack;
  handle_data->obj_uv = obj_self;
  handle_data->obj_goroutine = obj_goroutine;
  
  timer_handle->data = handle_data;
  
  int64_t timeout_nsec = env->get_field_long_by_name(env, stack, obj_goroutine, "timeout_duration_nsec", &error_id, __func__, FILE_NAME, __LINE__);
  int64_t timeout_msec = timeout_nsec / 1000000;
  uv_timer_start(timer_handle, on_timer_callback, timeout_msec, 0);
  
  return 0;
}
