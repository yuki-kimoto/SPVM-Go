// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>

#include "spvm_native.h"
#include "uv.h"

static const char* FILE_NAME = "Go/UV.c";

void boot_Go__UV(void) {
  
}

int32_t SPVM__Go__UV__run(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  uv_loop_t* uv_loop = uv_default_loop();
  
  int32_t status = uv_run(uv_loop, UV_RUN_DEFAULT);
  
  return 0;
}

typedef struct {
  SPVM_ENV* env;
  SPVM_VALUE* stack;
  SPVM_OBJ* obj_uv;
  SPVM_OBJ* obj_goroutine;
  uv_handle_t* related_handle;
} SPVM__Go__UV__HANDLE_DATA;

static void SPVM__Go__UV__close_cb(uv_handle_t* handle) {
  SPVM__Go__UV__HANDLE_DATA* handle_data = (SPVM__Go__UV__HANDLE_DATA*)handle->data;
  
  SPVM_ENV* env = handle_data->env;
  SPVM_VALUE* stack = handle_data->stack;
  
  env->free_memory_block(env, stack, handle_data);
  handle->data = NULL;
  env->free_memory_block(env, stack, handle);
}

static void SPVM__Go__UV__enable_goroutine_cb(uv_handle_t* handle) {
  
  int32_t error_id = 0;
  
  SPVM__Go__UV__HANDLE_DATA* handle_data = (SPVM__Go__UV__HANDLE_DATA*)handle->data;
  
  SPVM_ENV* env = handle_data->env;
  SPVM_VALUE* stack = handle_data->stack;
  SPVM_OBJ* obj_uv = handle_data->obj_uv;
  SPVM_OBJ* obj_goroutine = handle_data->obj_goroutine;
  
  SPVM_OBJ* obj_schedule = env->get_field_object_by_name(env, stack, obj_uv, "schedule", &error_id, __func__, FILE_NAME, __LINE__);
  if (!obj_schedule) {
    spvm_diag("[Unexcepted Error]Can't get Go::Schedule object.");
    abort();
  }
  assert(obj_schedule);
  
  stack[0].oval = obj_schedule;
  stack[1].oval = obj_goroutine;
  
  env->call_instance_method_by_name(env, stack, "enable_goroutine", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (!(error_id == 0)) {
    spvm_diag("[Unexcepted Error]enable_goroutine method failed.");
    abort();
  }
  
  uv_handle_t* related_handle = handle_data->related_handle;
  if (related_handle) {
    int32_t handle_type = uv_handle_get_type((uv_handle_t*)handle);
    if (handle_type == UV_TIMER) {
      // IO timeout
      env->set_field_int_by_name(env, stack, obj_goroutine, "io_wait_over_deadline", 1, &error_id, __func__, FILE_NAME, __LINE__);
      if (!(error_id == 0)) {
        spvm_diag("[Unexcepted Error]Setting 'io_wait_over_deadline' field failed.");
        abort();
      }
    }
    uv_close(related_handle, SPVM__Go__UV__close_cb);
  }
  
  uv_close((uv_handle_t*)handle, SPVM__Go__UV__close_cb);
}

static void SPVM__Go__UV__enable_goroutine_cb_for_poll(uv_poll_t* handle, int status, int events) {
  SPVM__Go__UV__enable_goroutine_cb((uv_handle_t*)handle);
}

static void SPVM__Go__UV__enable_goroutine_cb_for_timer(uv_timer_t* handle) {
  SPVM__Go__UV__enable_goroutine_cb((uv_handle_t*)handle);
}

int32_t SPVM__Go__UV__timer(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  SPVM_OBJ* obj_self = stack[0].oval;
  SPVM_OBJ* obj_goroutine = stack[1].oval;
  
  uv_loop_t* uv_loop = uv_default_loop();
  uv_timer_t* timer_handle = env->new_memory_block(env, stack, sizeof(uv_timer_t));
  uv_timer_init(uv_loop, timer_handle);
  
  SPVM__Go__UV__HANDLE_DATA* timer_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
  timer_handle_data->env = env;
  timer_handle_data->stack = stack;
  timer_handle_data->obj_uv = obj_self;
  timer_handle_data->obj_goroutine = obj_goroutine;
  
  timer_handle->data = timer_handle_data;
  
  int64_t timeout_nsec = env->get_field_long_by_name(env, stack, obj_goroutine, "timeout_duration_nsec", &error_id, __func__, FILE_NAME, __LINE__);
  int64_t timeout_msec = timeout_nsec / 1000000;
  uv_timer_start(timer_handle, SPVM__Go__UV__enable_goroutine_cb_for_timer, timeout_msec, 0);
  
  return 0;
}

static void SPVM__Go__UV__process_goroutine_cb(uv_idle_t* handle) {
  int32_t error_id = 0;
  
  SPVM__Go__UV__HANDLE_DATA* handle_data = (SPVM__Go__UV__HANDLE_DATA*)handle->data;
  
  SPVM_ENV* env = handle_data->env;
  SPVM_VALUE* stack = handle_data->stack;
  SPVM_OBJ* obj_uv = handle_data->obj_uv;
  
  SPVM_OBJ* obj_schedule = env->get_field_object_by_name(env, stack, obj_uv, "schedule", &error_id, __func__, FILE_NAME, __LINE__);
  if (!obj_schedule) {
    spvm_diag("[Unexcepted Error]Can't get Go::Schedule object.");
    abort();
  }
  
  stack[0].oval = obj_schedule;
  env->call_instance_method_by_name(env, stack, "process_next_goroutine", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (!(error_id == 0)) {
    spvm_diag("[Unexcepted Error]Go::UV#process_next_goroutine method failed.");
    abort();
  }
  
  stack[0].oval = obj_uv;
  env->call_instance_method_by_name(env, stack, "loop_alive", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (!(error_id == 0)) {
    spvm_diag("[Unexcepted Error]Go::UV#loop_alive method failed.");
    abort();
  }
  int32_t loop_alive = stack[0].ival;
  
  if (!loop_alive) {
    uv_idle_stop(handle);
    uv_close((uv_handle_t*)handle, SPVM__Go__UV__close_cb);
  }
}

int32_t SPVM__Go__UV__idle_start(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_self = stack[0].oval;
  
  uv_loop_t* uv_loop = uv_default_loop();
  uv_idle_t* idle_handle = env->new_memory_block(env, stack, sizeof(uv_idle_t));
  uv_idle_init(uv_loop, idle_handle);
  
  SPVM__Go__UV__HANDLE_DATA* handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
  handle_data->env = env;
  handle_data->stack = stack;
  handle_data->obj_uv = obj_self;
  
  idle_handle->data = handle_data;
  
  uv_idle_start(idle_handle, SPVM__Go__UV__process_goroutine_cb);
  
  return 0;
}

int32_t SPVM__Go__UV__poll_socket(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  SPVM_OBJ* obj_self = stack[0].oval;
  SPVM_OBJ* obj_goroutine = stack[1].oval;
  
  uv_loop_t* uv_loop = uv_default_loop();
  uv_poll_t* poll_handle = env->new_memory_block(env, stack, sizeof(uv_poll_t));
  int32_t fd = env->get_field_int_by_name(env, stack, obj_goroutine, "fd", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  int32_t schedule_type = env->get_field_int_by_name(env, stack, obj_goroutine, "schedule_type", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  env->call_class_method_by_name(env, stack, "Go::Schedule", "TYPE_IO_READ", 0, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  int32_t schedule_type_io_read = stack[0].ival;
  
  uv_poll_init_socket(uv_loop, poll_handle, fd);
  
  SPVM__Go__UV__HANDLE_DATA* poll_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
  poll_handle_data->env = env;
  poll_handle_data->stack = stack;
  poll_handle_data->obj_uv = obj_self;
  poll_handle_data->obj_goroutine = obj_goroutine;
  
  poll_handle->data = poll_handle_data;
  
  int32_t poll_events = (schedule_type == schedule_type_io_read) ? UV_READABLE : UV_WRITABLE;
  uv_poll_start(poll_handle, poll_events, SPVM__Go__UV__enable_goroutine_cb_for_poll);
  
  int64_t timeout_nsec = env->get_field_long_by_name(env, stack, obj_goroutine, "timeout_duration_nsec", &error_id, __func__, FILE_NAME, __LINE__);
  if (timeout_nsec > 0) {
    uv_timer_t* timer_handle = env->new_memory_block(env, stack, sizeof(uv_timer_t));
    uv_timer_init(uv_loop, timer_handle);
    
    SPVM__Go__UV__HANDLE_DATA* timer_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
    timer_handle_data->env = env;
    timer_handle_data->stack = stack;
    timer_handle_data->obj_uv = obj_self;
    timer_handle_data->obj_goroutine = obj_goroutine;
    
    timer_handle->data = timer_handle_data;
    
    poll_handle_data->related_handle = (uv_handle_t*)timer_handle;
    timer_handle_data->related_handle = (uv_handle_t*)poll_handle;
    
    int64_t timeout_msec = timeout_nsec / 1000000;
    uv_timer_start(timer_handle, SPVM__Go__UV__enable_goroutine_cb_for_timer, timeout_msec, 0);
  }
  
  return 0;
}
