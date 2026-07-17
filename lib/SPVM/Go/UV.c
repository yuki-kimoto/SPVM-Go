// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>

#include "spvm_native.h"
#include "uv.h"

static const char* FILE_NAME = "Go/UV.c";

typedef struct {
  SPVM_ENV* env;
  SPVM_VALUE* stack;
  SPVM_OBJ* obj_uv;
  SPVM_OBJ* obj_uv_handle;
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
  SPVM_OBJ* obj_uv_handle = handle_data->obj_uv_handle;
  
  SPVM_OBJ* obj_cb = env->get_field_object_by_name(env, stack, obj_uv_handle, "cb", &error_id, __func__, FILE_NAME, __LINE__);
  assert(obj_cb);
  stack[0].oval = obj_cb;
  env->call_instance_method_by_name(env, stack, "", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (!(error_id == 0)) {
    spvm_diag("[Unexcepted Error]Callback 'cb' failed.");
    abort();
  }
  
  uv_handle_t* related_handle = handle_data->related_handle;
  if (related_handle) {
    int32_t handle_type = uv_handle_get_type((uv_handle_t*)handle);
    if (handle_type == UV_TIMER) {
      // IO timeout
      env->set_field_int_by_name(env, stack, obj_uv_handle, "io_timeout_occurred", 1, &error_id, __func__, FILE_NAME, __LINE__);
      if (!(error_id == 0)) {
        spvm_diag("[Unexcepted Error]Setting 'io_timeout_occurred' field failed.");
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

int32_t SPVM__Go__UV__run(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  uv_loop_t* uv_loop = uv_default_loop();
  
  int32_t status = uv_run(uv_loop, UV_RUN_DEFAULT);
  
  return 0;
}

int32_t SPVM__Go__UV__run_v2(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_self = stack[0].oval;
  SPVM_OBJ* obj_uv_loop = stack[1].oval;
  
  uv_loop_t* uv_loop = env->get_pointer(env, stack, obj_uv_loop);
  assert(uv_loop);
  
  int32_t status = uv_run(uv_loop, UV_RUN_DEFAULT);
  
  return 0;
}

int32_t SPVM__Go__UV__timer(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  SPVM_OBJ* obj_self = stack[0].oval;
  SPVM_OBJ* obj_uv_handle = stack[1].oval;
  
  uv_loop_t* uv_loop = uv_default_loop();
  uv_timer_t* timer_handle = env->new_memory_block(env, stack, sizeof(uv_timer_t));
  uv_timer_init(uv_loop, timer_handle);
  
  SPVM__Go__UV__HANDLE_DATA* timer_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
  timer_handle_data->env = env;
  timer_handle_data->stack = stack;
  timer_handle_data->obj_uv = obj_self;
  timer_handle_data->obj_uv_handle = obj_uv_handle;
  
  timer_handle->data = timer_handle_data;
  
  int64_t timeout_msec = env->get_field_long_by_name(env, stack, obj_uv_handle, "timeout_msec", &error_id, __func__, FILE_NAME, __LINE__);
  uv_timer_start(timer_handle, SPVM__Go__UV__enable_goroutine_cb_for_timer, timeout_msec, 0);
  
  return 0;
}

int32_t SPVM__Go__UV__timer_v2(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  SPVM_OBJ* obj_self = stack[0].oval;
  SPVM_OBJ* obj_uv_loop = stack[1].oval;
  SPVM_OBJ* obj_uv_handle = stack[2].oval;
  
  uv_loop_t* uv_loop = env->get_pointer(env, stack, obj_uv_loop);
  uv_timer_t* timer_handle = env->new_memory_block(env, stack, sizeof(uv_timer_t));
  uv_timer_init(uv_loop, timer_handle);
  
  SPVM__Go__UV__HANDLE_DATA* timer_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
  timer_handle_data->env = env;
  timer_handle_data->stack = stack;
  timer_handle_data->obj_uv = obj_self;
  timer_handle_data->obj_uv_handle = obj_uv_handle;
  
  timer_handle->data = timer_handle_data;
  
  int64_t timeout_msec = env->get_field_long_by_name(env, stack, obj_uv_handle, "timeout_msec", &error_id, __func__, FILE_NAME, __LINE__);
  uv_timer_start(timer_handle, SPVM__Go__UV__enable_goroutine_cb_for_timer, timeout_msec, 0);
  
  return 0;
}


static void SPVM__Go__UV__idle_cb(uv_idle_t* handle) {
  int32_t error_id = 0;
  
  SPVM__Go__UV__HANDLE_DATA* handle_data = (SPVM__Go__UV__HANDLE_DATA*)handle->data;
  
  SPVM_ENV* env = handle_data->env;
  SPVM_VALUE* stack = handle_data->stack;
  SPVM_OBJ* obj_uv = handle_data->obj_uv;
  SPVM_OBJ* obj_uv_handle = handle_data->obj_uv_handle;
  
  SPVM_OBJ* obj_cb = env->get_field_object_by_name(env, stack, obj_uv_handle, "cb", &error_id, __func__, FILE_NAME, __LINE__);
  assert(obj_cb);
  stack[0].oval = obj_cb;
  env->call_instance_method_by_name(env, stack, "", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (!(error_id == 0)) {
    spvm_diag("[Unexcepted Error]Callback 'cb' failed.");
    abort();
  }
  
  SPVM_OBJ* obj_loop_alive_cb = env->get_field_object_by_name(env, stack, obj_uv_handle, "loop_alive_cb", &error_id, __func__, FILE_NAME, __LINE__);
  assert(obj_loop_alive_cb);
  stack[0].oval = obj_loop_alive_cb;
  env->call_instance_method_by_name(env, stack, "", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (!(error_id == 0)) {
    spvm_diag("[Unexcepted Error]Callback 'loop_alive_cb' failed.");
    abort();
  }
  int32_t loop_alive = stack[0].ival;
  
  if (!loop_alive) {
    uv_idle_stop(handle);
    uv_close((uv_handle_t*)handle, SPVM__Go__UV__close_cb);
  }
}

int32_t SPVM__Go__UV__idle(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_self = stack[0].oval;
  SPVM_OBJ* obj_uv_handle = stack[1].oval;
  
  uv_loop_t* uv_loop = uv_default_loop();
  uv_idle_t* idle_handle = env->new_memory_block(env, stack, sizeof(uv_idle_t));
  uv_idle_init(uv_loop, idle_handle);
  
  SPVM__Go__UV__HANDLE_DATA* handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
  handle_data->env = env;
  handle_data->stack = stack;
  handle_data->obj_uv = obj_self;
  handle_data->obj_uv_handle = obj_uv_handle;
  
  idle_handle->data = handle_data;
  
  uv_idle_start(idle_handle, SPVM__Go__UV__idle_cb);
  
  return 0;
}

int32_t SPVM__Go__UV__idle_v2(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_self = stack[0].oval;
  SPVM_OBJ* obj_uv_loop = stack[1].oval;
  SPVM_OBJ* obj_uv_handle = stack[2].oval;
  
  uv_loop_t* uv_loop = env->get_pointer(env, stack, obj_uv_loop);
  uv_idle_t* idle_handle = env->new_memory_block(env, stack, sizeof(uv_idle_t));
  uv_idle_init(uv_loop, idle_handle);
  
  SPVM__Go__UV__HANDLE_DATA* handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
  handle_data->env = env;
  handle_data->stack = stack;
  handle_data->obj_uv = obj_self;
  handle_data->obj_uv_handle = obj_uv_handle;
  
  idle_handle->data = handle_data;
  
  uv_idle_start(idle_handle, SPVM__Go__UV__idle_cb);
  
  return 0;
}

int32_t SPVM__Go__UV__poll(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  SPVM_OBJ* obj_self = stack[0].oval;
  SPVM_OBJ* obj_uv_handle = stack[1].oval;
  
  uv_loop_t* uv_loop = uv_default_loop();
  uv_poll_t* poll_handle = env->new_memory_block(env, stack, sizeof(uv_poll_t));
  int32_t fd = env->get_field_int_by_name(env, stack, obj_uv_handle, "fd", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  int32_t event_type = env->get_field_int_by_name(env, stack, obj_uv_handle, "event_type", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  uv_poll_init(uv_loop, poll_handle, fd);
  
  SPVM__Go__UV__HANDLE_DATA* poll_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
  poll_handle_data->env = env;
  poll_handle_data->stack = stack;
  poll_handle_data->obj_uv = obj_self;
  poll_handle_data->obj_uv_handle = obj_uv_handle;
  
  poll_handle->data = poll_handle_data;
  
  uv_poll_start(poll_handle, event_type, SPVM__Go__UV__enable_goroutine_cb_for_poll);
  
  int64_t timeout_msec = env->get_field_long_by_name(env, stack, obj_uv_handle, "timeout_msec", &error_id, __func__, FILE_NAME, __LINE__);
  if (timeout_msec > 0) {
    uv_timer_t* timer_handle = env->new_memory_block(env, stack, sizeof(uv_timer_t));
    uv_timer_init(uv_loop, timer_handle);
    
    SPVM__Go__UV__HANDLE_DATA* timer_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
    timer_handle_data->env = env;
    timer_handle_data->stack = stack;
    timer_handle_data->obj_uv = obj_self;
    timer_handle_data->obj_uv_handle = obj_uv_handle;
    
    timer_handle->data = timer_handle_data;
    
    poll_handle_data->related_handle = (uv_handle_t*)timer_handle;
    timer_handle_data->related_handle = (uv_handle_t*)poll_handle;
    
    uv_timer_start(timer_handle, SPVM__Go__UV__enable_goroutine_cb_for_timer, timeout_msec, 0);
  }
  
  return 0;
}

int32_t SPVM__Go__UV__poll_v2(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  SPVM_OBJ* obj_self = stack[0].oval;
  SPVM_OBJ* obj_uv_loop = stack[1].oval;
  SPVM_OBJ* obj_uv_handle = stack[2].oval;
  
  uv_loop_t* uv_loop = env->get_pointer(env, stack, obj_uv_loop);
  uv_poll_t* poll_handle = env->new_memory_block(env, stack, sizeof(uv_poll_t));
  int32_t fd = env->get_field_int_by_name(env, stack, obj_uv_handle, "fd", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  int32_t event_type = env->get_field_int_by_name(env, stack, obj_uv_handle, "event_type", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  uv_poll_init(uv_loop, poll_handle, fd);
  
  SPVM__Go__UV__HANDLE_DATA* poll_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
  poll_handle_data->env = env;
  poll_handle_data->stack = stack;
  poll_handle_data->obj_uv = obj_self;
  poll_handle_data->obj_uv_handle = obj_uv_handle;
  
  poll_handle->data = poll_handle_data;
  
  uv_poll_start(poll_handle, event_type, SPVM__Go__UV__enable_goroutine_cb_for_poll);
  
  int64_t timeout_msec = env->get_field_long_by_name(env, stack, obj_uv_handle, "timeout_msec", &error_id, __func__, FILE_NAME, __LINE__);
  if (timeout_msec > 0) {
    uv_timer_t* timer_handle = env->new_memory_block(env, stack, sizeof(uv_timer_t));
    uv_timer_init(uv_loop, timer_handle);
    
    SPVM__Go__UV__HANDLE_DATA* timer_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
    timer_handle_data->env = env;
    timer_handle_data->stack = stack;
    timer_handle_data->obj_uv = obj_self;
    timer_handle_data->obj_uv_handle = obj_uv_handle;
    
    timer_handle->data = timer_handle_data;
    
    poll_handle_data->related_handle = (uv_handle_t*)timer_handle;
    timer_handle_data->related_handle = (uv_handle_t*)poll_handle;
    
    uv_timer_start(timer_handle, SPVM__Go__UV__enable_goroutine_cb_for_timer, timeout_msec, 0);
  }
  
  return 0;
}

static void SPVM__Go__UV__enable_goroutine_cb_for_async(uv_async_t* handle) {
  
  SPVM__Go__UV__enable_goroutine_cb((uv_handle_t*)handle);
}

int32_t SPVM__Go__UV__async(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_self = stack[0].oval;
  SPVM_OBJ* obj_uv_handle = stack[1].oval;
  
  uv_loop_t* uv_loop = uv_default_loop();
  uv_async_t* address = env->new_memory_block(env, stack, sizeof(uv_async_t));
  uv_async_init(uv_loop, address, SPVM__Go__UV__enable_goroutine_cb_for_async);
  
  SPVM__Go__UV__HANDLE_DATA* handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
  handle_data->env = env;
  handle_data->stack = stack;
  handle_data->obj_uv = obj_self;
  handle_data->obj_uv_handle = obj_uv_handle;
  
  address->data = handle_data;
  
  SPVM_OBJ* obj_address = env->new_pointer_object_by_name(env, stack, "Address", address, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_uv_handle, "address", obj_address, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__Go__UV__async_v2(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_self = stack[0].oval;
  SPVM_OBJ* obj_uv_loop = stack[1].oval;
  SPVM_OBJ* obj_uv_handle = stack[2].oval;
  
  uv_loop_t* uv_loop = env->get_pointer(env, stack, obj_uv_loop);
  uv_async_t* address = env->new_memory_block(env, stack, sizeof(uv_async_t));
  uv_async_init(uv_loop, address, SPVM__Go__UV__enable_goroutine_cb_for_async);
  
  SPVM__Go__UV__HANDLE_DATA* handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__HANDLE_DATA));
  handle_data->env = env;
  handle_data->stack = stack;
  handle_data->obj_uv = obj_self;
  handle_data->obj_uv_handle = obj_uv_handle;
  
  address->data = handle_data;
  
  SPVM_OBJ* obj_address = env->new_pointer_object_by_name(env, stack, "Address", address, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_uv_handle, "address", obj_address, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__Go__UV__async_send(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_handle = stack[1].oval;
  
  SPVM_OBJ* obj_address = env->get_field_object_by_name(env, stack, obj_uv_handle, "address", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  uv_async_t* address = (uv_async_t*)env->get_pointer(env, stack, obj_address);
  
  uv_async_send(address);
  
  env->set_field_object_by_name(env, stack, obj_uv_handle, "address", NULL, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}
