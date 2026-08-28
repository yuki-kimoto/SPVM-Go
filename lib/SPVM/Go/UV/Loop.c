// Copyright (c) 2026 Yuki Kimoto
// MIT License

#include "spvm_native.h"
#include "uv.h"
#include "spvm_go_uv.h"

static const char* FILE_NAME = "Go/UV/Loop.c";

int32_t SPVM__Go__UV__Loop__default_loop(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_loop = env->get_class_var_object_by_name(env, stack, "Go::UV::Loop", "$DEFAULT_LOOP", &error_id, __func__, FILE_NAME, __LINE__);
  
  if (!obj_uv_loop) {
    uv_loop_t* uv_loop = uv_default_loop();
    
    obj_uv_loop = env->new_pointer_object_by_name(env, stack, "Go::UV::Loop", uv_loop, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) return error_id;
    
    env->set_no_free(env, stack, obj_uv_loop, 1);
    
    stack[0].oval = obj_uv_loop;
    env->call_instance_method_by_name(env, stack, "init", 1, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) return error_id;
    
    env->set_class_var_object_by_name(env, stack, "Go::UV::Loop", "$DEFAULT_LOOP", obj_uv_loop, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) return error_id;
  }
  
  stack[0].oval = obj_uv_loop;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_loop_t* uv_loop = env->new_memory_block(env, stack, sizeof(uv_loop_t));
  
  int32_t status = uv_loop_init(uv_loop);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_loop_init failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  SPVM_OBJ* obj_uv_loop = env->new_pointer_object_by_name(env, stack, "Go::UV::Loop", uv_loop, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  stack[0].oval = obj_uv_loop;
  env->call_instance_method_by_name(env, stack, "init", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  stack[0].oval = obj_uv_loop;
  
  return 0;
}

static void SPVM__Go__UV__Loop__async_cb(uv_async_t* uv_handle) {
  
  int32_t error_id = 0;
  
  SPVM__Go__UV__Handle__HANDLE_DATA* uv_handle_data = (SPVM__Go__UV__Handle__HANDLE_DATA*)uv_handle->data;
  
  SPVM_ENV* env = uv_handle_data->env;
  SPVM_VALUE* stack = uv_handle_data->stack;
  SPVM_OBJ* obj_uv_handle = uv_handle_data->obj_uv_handle;
  SPVM_OBJ* obj_cb = env->get_field_object_by_name(env, stack, obj_uv_handle, "async_cb", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]Getting 'async_cb' field failed.");
    abort();
  }
  
  stack[0].oval = obj_cb;
  stack[1].oval = obj_uv_handle;
  env->call_instance_method_by_name(env, stack, "", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[An exception is converted to a warning in SPVM__Go__UV__Loop__async_cb]\n%s", env->get_exception_chars(env, stack));
    return;
  }
  
}

int32_t SPVM__Go__UV__Loop__run(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_uv_loop = stack[0].oval;
  int32_t uv_run_mode = stack[1].ival;
  
  uv_loop_t* uv_loop = env->get_pointer(env, stack, obj_uv_loop);
  assert(uv_loop);
  
  int32_t status = uv_run(uv_loop, uv_run_mode);
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__idle_init(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_loop = stack[0].oval;
  SPVM_OBJ* obj_uv_idle = stack[1].oval;
  
  if (!obj_uv_idle) {
    return env->die(env, stack, "$uv_idle must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  uv_loop_t* uv_loop = env->get_pointer(env, stack, obj_uv_loop);
  uv_idle_t* uv_idle = env->get_pointer(env, stack, obj_uv_idle);
  
  int32_t status = uv_idle_init(uv_loop, uv_idle);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_idle_init failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  stack[0].oval = obj_uv_loop;
  stack[1].oval = obj_uv_idle;
  env->call_instance_method_by_name(env, stack, "set_uv_handle", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__async_init(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_loop = stack[0].oval;
  SPVM_OBJ* obj_uv_async = stack[1].oval;
  SPVM_OBJ* obj_cb = stack[2].oval;
  
  if (!obj_uv_async) {
    return env->die(env, stack, "$uv_async must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_cb) {
    return env->die(env, stack, "$cb must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  uv_loop_t* uv_loop = env->get_pointer(env, stack, obj_uv_loop);
  uv_async_t* uv_async = env->get_pointer(env, stack, obj_uv_async);
  
  env->set_field_object_by_name(env, stack, obj_uv_async, "async_cb", obj_cb, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  int32_t status = uv_async_init(uv_loop, uv_async, SPVM__Go__UV__Loop__async_cb);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_async_init failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  stack[0].oval = obj_uv_loop;
  stack[1].oval = obj_uv_async;
  env->call_instance_method_by_name(env, stack, "set_uv_handle", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__timer_init(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_loop = stack[0].oval;
  SPVM_OBJ* obj_uv_timer = stack[1].oval;
  
  if (!obj_uv_timer) {
    return env->die(env, stack, "$uv_timer must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  uv_loop_t* uv_loop = env->get_pointer(env, stack, obj_uv_loop);
  uv_timer_t* uv_timer = env->get_pointer(env, stack, obj_uv_timer);
  
  int32_t status = uv_timer_init(uv_loop, uv_timer);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_timer_init failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  stack[0].oval = obj_uv_loop;
  stack[1].oval = obj_uv_timer;
  env->call_instance_method_by_name(env, stack, "set_uv_handle", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__poll_init(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_loop = stack[0].oval;
  SPVM_OBJ* obj_uv_poll = stack[1].oval;
  int32_t fd = stack[2].ival;
  
  if (!obj_uv_poll) {
    return env->die(env, stack, "$uv_poll must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  uv_loop_t* uv_loop = env->get_pointer(env, stack, obj_uv_loop);
  uv_poll_t* uv_poll = env->get_pointer(env, stack, obj_uv_poll);
  
  int32_t status = uv_poll_init(uv_loop, uv_poll, fd);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_poll_init failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  stack[0].oval = obj_uv_loop;
  stack[1].oval = obj_uv_poll;
  env->call_instance_method_by_name(env, stack, "set_uv_handle", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__pipe_init(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_loop = stack[0].oval;
  SPVM_OBJ* obj_uv_pipe = stack[1].oval;
  int32_t ipc = stack[2].ival;
  
  if (!obj_uv_pipe) {
    return env->die(env, stack, "$uv_pipe must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  uv_loop_t* uv_loop = env->get_pointer(env, stack, obj_uv_loop);
  uv_pipe_t* uv_pipe = env->get_pointer(env, stack, obj_uv_pipe);
  
  int32_t status = uv_pipe_init(uv_loop, uv_pipe, ipc);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_pipe_init failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  stack[0].oval = obj_uv_loop;
  stack[1].oval = obj_uv_pipe;
  env->call_instance_method_by_name(env, stack, "set_uv_handle", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_loop = stack[0].oval;
  
  uv_loop_t* uv_loop = env->get_pointer(env, stack, obj_uv_loop);
  
  int32_t status = uv_loop_close(uv_loop);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_loop_close failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  int32_t no_free = env->no_free(env, stack, obj_uv_loop);
  if (!no_free) {
    env->free_memory_block(env, stack, uv_loop);
    env->set_no_free(env, stack, obj_uv_loop, 1);
  }
  
  return 0;
}
