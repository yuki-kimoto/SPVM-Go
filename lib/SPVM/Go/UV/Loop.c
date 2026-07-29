// Copyright (c) 2026 Yuki Kimoto
// MIT License

#include "spvm_native.h"
#include "uv.h"

static const char* FILE_NAME = "Go/UV/Loop.c";

typedef struct {
  SPVM_ENV* env;
  SPVM_VALUE* stack;
  SPVM_OBJ* uv_handle;
} SPVM__Go__UV__Loop__DATA;

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

int32_t SPVM__Go__UV__Loop__strerror(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int32_t status = stack[0].ival;
  
  char uv_strerror[512];
  uv_strerror_r(status, uv_strerror, sizeof(uv_strerror));
  
  SPVM_OBJ* obj_uv_strerror = env->new_string_nolen(env, stack, uv_strerror);
  
  stack[0].oval = obj_uv_strerror;
  
  return 0;
}

static void SPVM__Go__UV__Loop__close_cb(uv_handle_t* uv_handle) {
  
  int32_t error_id = 0;
  
  SPVM__Go__UV__Loop__DATA* uv_data = (SPVM__Go__UV__Loop__DATA*)uv_handle->data;
  
  SPVM_ENV* env = uv_data->env;
  SPVM_VALUE* stack = uv_data->stack;
  SPVM_OBJ* obj_uv_handle = uv_data->uv_handle;
  SPVM_OBJ* obj_cb = env->get_field_object_by_name(env, stack, obj_uv_handle, "close_cb", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]Getting 'close_cb' field failed.");
    abort();
  }
  
  if (obj_cb) {
    stack[0].oval = obj_cb;
    stack[1].oval = obj_uv_handle;
    env->call_instance_method_by_name(env, stack, "", 2, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) {
      spvm_diag("[An exception is converted to a warning in SPVM__Go__UV__Loop__close_cb]\n%s", env->get_exception_chars(env, stack));
      return;
    }
  }
  
  SPVM_OBJ* obj_uv_loop = env->get_field_object_by_name(env, stack, obj_uv_handle, "loop", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]Getting 'loop' field failed.");
    abort();
  }
  
  stack[0].oval = obj_uv_loop;
  stack[1].oval = obj_uv_handle;
  env->call_instance_method_by_name(env, stack, "delete_uv_handle", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]Calling 'delete_uv_handle' failed.");
    abort();
  }
}

static void SPVM__Go__UV__Loop__idle_cb(uv_idle_t* uv_handle) {
  
  int32_t error_id = 0;
  
  SPVM__Go__UV__Loop__DATA* uv_data = (SPVM__Go__UV__Loop__DATA*)uv_handle->data;
  
  SPVM_ENV* env = uv_data->env;
  SPVM_VALUE* stack = uv_data->stack;
  SPVM_OBJ* obj_uv_handle = uv_data->uv_handle;
  SPVM_OBJ* obj_cb = env->get_field_object_by_name(env, stack, obj_uv_handle, "idle_cb", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]Getting 'idle_cb' field failed.");
    abort();
  }
  
  stack[0].oval = obj_cb;
  stack[1].oval = obj_uv_handle;
  env->call_instance_method_by_name(env, stack, "", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[An exception is converted to a warning in SPVM__Go__UV__Loop__idle_cb]\n%s", env->get_exception_chars(env, stack));
    return;
  }
  
}

static void SPVM__Go__UV__Loop__async_cb(uv_async_t* uv_handle) {
  
  int32_t error_id = 0;
  
  SPVM__Go__UV__Loop__DATA* uv_data = (SPVM__Go__UV__Loop__DATA*)uv_handle->data;
  
  SPVM_ENV* env = uv_data->env;
  SPVM_VALUE* stack = uv_data->stack;
  SPVM_OBJ* obj_uv_handle = uv_data->uv_handle;
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

static void SPVM__Go__UV__Loop__timer_cb(uv_timer_t* uv_handle) {
  
  int32_t error_id = 0;
  
  SPVM__Go__UV__Loop__DATA* uv_data = (SPVM__Go__UV__Loop__DATA*)uv_handle->data;
  
  SPVM_ENV* env = uv_data->env;
  SPVM_VALUE* stack = uv_data->stack;
  SPVM_OBJ* obj_uv_handle = uv_data->uv_handle;
  SPVM_OBJ* obj_cb = env->get_field_object_by_name(env, stack, obj_uv_handle, "timer_cb", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]Getting 'timer_cb' field failed.");
    abort();
  }
  
  stack[0].oval = obj_cb;
  stack[1].oval = obj_uv_handle;
  env->call_instance_method_by_name(env, stack, "", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[An exception is converted to a warning in SPVM__Go__UV__Loop__timer_cb]\n%s", env->get_exception_chars(env, stack));
    return;
  }
  
}

static void SPVM__Go__UV__Loop__poll_cb(uv_poll_t* uv_handle, int status, int event) {
  
  int32_t error_id = 0;
  
  SPVM__Go__UV__Loop__DATA* uv_data = (SPVM__Go__UV__Loop__DATA*)uv_handle->data;
  
  SPVM_ENV* env = uv_data->env;
  SPVM_VALUE* stack = uv_data->stack;
  SPVM_OBJ* obj_uv_handle = uv_data->uv_handle;
  SPVM_OBJ* obj_cb = env->get_field_object_by_name(env, stack, obj_uv_handle, "poll_cb", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]Getting 'poll_cb' field failed.");
    abort();
  }
  
  stack[0].oval = obj_cb;
  stack[1].oval = obj_uv_handle;
  stack[2].ival = status;
  stack[3].ival = event;
  env->call_instance_method_by_name(env, stack, "", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[An exception is converted to a warning in SPVM__Go__UV__Loop__poll_cb]\n%s", env->get_exception_chars(env, stack));
    return;
  }
  
}

void SPVM__Go__UV__Loop__read_cb(uv_stream_t* uv_handle, ssize_t nread, const uv_buf_t* buf) {
  
  int32_t error_id = 0;
  
  SPVM__Go__UV__Loop__DATA* uv_data = (SPVM__Go__UV__Loop__DATA*)uv_handle->data;
  
  SPVM_ENV* env = uv_data->env;
  SPVM_VALUE* stack = uv_data->stack;
  SPVM_OBJ* obj_uv_handle = uv_data->uv_handle;
  SPVM_OBJ* obj_cb = env->get_field_object_by_name(env, stack, obj_uv_handle, "read_cb", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]Getting 'read_cb' field failed.");
    abort();
  }
  
  SPVM_OBJ* obj_read_buffer = env->get_field_object_by_name(env, stack, obj_uv_handle, "read_buffer", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]Getting 'read_buffer' field failed.");
    abort();
  }
  
  assert(obj_cb);
  stack[0].oval = obj_cb;
  stack[1].oval = obj_uv_handle;
  stack[2].ival = nread;
  stack[3].oval = obj_read_buffer;
  env->call_instance_method_by_name(env, stack, "", 4, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[An exception is converted to a warning in SPVM__Go__UV__Loop__read_cb]\n%s", env->get_exception_chars(env, stack));
    return;
  }
  
}

void SPVM__Go__UV__Loop__write_cb(uv_write_t* uv_handle, int status) {
  
  int32_t error_id = 0;
  
  SPVM__Go__UV__Loop__DATA* uv_data = (SPVM__Go__UV__Loop__DATA*)uv_handle->data;
  
  SPVM_ENV* env = uv_data->env;
  SPVM_VALUE* stack = uv_data->stack;
  SPVM_OBJ* obj_uv_handle = uv_data->uv_handle;
  SPVM_OBJ* obj_cb = env->get_field_object_by_name(env, stack, obj_uv_handle, "write_cb", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]Getting 'write_cb' field failed.");
    abort();
  }
  
  assert(obj_cb);
  stack[0].oval = obj_cb;
  stack[1].oval = obj_uv_handle;
  stack[2].ival = status;
  env->call_instance_method_by_name(env, stack, "", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[An exception is converted to a warning in SPVM__Go__UV__Loop__write_cb]\n%s", env->get_exception_chars(env, stack));
    return;
  }
  
}

int32_t SPVM__Go__UV__Loop__run(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_uv_loop = stack[0].oval;
  int32_t uv_run_mode = stack[1].ival;
  
  uv_loop_t* uv_loop = env->get_pointer(env, stack, obj_uv_loop);
  assert(uv_loop);
  
  int32_t status = uv_run(uv_loop, uv_run_mode);
  
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

int32_t SPVM__Go__UV__Loop__new_poll(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_poll_t* uv_poll = env->new_memory_block(env, stack, sizeof(uv_poll_t));
  
  SPVM__Go__UV__Loop__DATA* uv_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Loop__DATA));
  uv_data->env = env;
  uv_data->stack = stack;
  
  uv_poll->data = uv_data;
  
  SPVM_OBJ* obj_uv_poll = env->new_pointer_object_by_name(env, stack, "Go::UV::Handle::Poll", uv_poll, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_data->uv_handle = obj_uv_poll;
  
  stack[0].oval = obj_uv_poll;
  
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

int32_t SPVM__Go__UV__Loop__handle_idle_start(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_idle = stack[0].oval;
  SPVM_OBJ* obj_cb = stack[1].oval;
  
  if (!obj_cb) {
    return env->die(env, stack, "$cb must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  uv_idle_t* uv_idle = env->get_pointer(env, stack, obj_uv_idle);
  SPVM__Go__UV__Loop__DATA* uv_idle_data = uv_idle->data;
  
  env->set_field_object_by_name(env, stack, obj_uv_idle, "idle_cb", obj_cb, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  int32_t status = uv_idle_start(uv_idle, SPVM__Go__UV__Loop__idle_cb);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_idle_start failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__handle_timer_start(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_timer = stack[0].oval;
  SPVM_OBJ* obj_cb = stack[1].oval;
  int64_t timeout_msec = stack[2].lval;
  int64_t interval_msec = stack[3].lval;
  
  if (!obj_cb) {
    return env->die(env, stack, "$cb must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  env->set_field_object_by_name(env, stack, obj_uv_timer, "timer_cb", obj_cb, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_timer_t* uv_timer = env->get_pointer(env, stack, obj_uv_timer);
  
  int32_t status = uv_timer_start(uv_timer, SPVM__Go__UV__Loop__timer_cb, (uint64_t)timeout_msec, (uint64_t)interval_msec);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_timer_start failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__handle_poll_start(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_poll = stack[0].oval;
  SPVM_OBJ* obj_cb = stack[1].oval;
  int32_t events = stack[2].ival;
  
  if (!obj_cb) {
    return env->die(env, stack, "$cb must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  env->set_field_object_by_name(env, stack, obj_uv_poll, "poll_cb", obj_cb, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_poll_t* uv_poll = env->get_pointer(env, stack, obj_uv_poll);
  
  int32_t status = uv_poll_start(uv_poll, events, SPVM__Go__UV__Loop__poll_cb);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_poll_start failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__handle_async_send(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_async = stack[0].oval;
  
  uv_async_t* uv_async = (uv_async_t*)env->get_pointer(env, stack, obj_uv_async);
  
  uv_async_send(uv_async);
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__handle_close(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_handle = stack[0].oval;
  SPVM_OBJ* obj_cb = stack[1].oval;
  
  env->set_field_object_by_name(env, stack, obj_uv_handle, "close_cb", obj_cb, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_handle_t* uv_handle = env->get_pointer(env, stack, obj_uv_handle);
  
  if (!uv_is_closing(uv_handle)) {
    uv_close(uv_handle, SPVM__Go__UV__Loop__close_cb);
  }
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__handle_free(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_uv_handle = stack[0].oval;
  
  int32_t no_free = env->no_free(env, stack, obj_uv_handle);
  
  if (!no_free) {
    uv_handle_t* uv_handle = env->get_pointer(env, stack, obj_uv_handle);
    
    SPVM__Go__UV__Loop__DATA* uv_data = (SPVM__Go__UV__Loop__DATA*)uv_handle->data;
    
    env->free_memory_block(env, stack, uv_data);
    uv_handle->data = NULL;
    env->free_memory_block(env, stack, uv_handle);
    env->set_no_free(env, stack, obj_uv_handle, 1);
  }
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__handle_get_type(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_handle = stack[0].oval;
  
  uv_handle_t* uv_handle = env->get_pointer(env, stack, obj_uv_handle);
  
  int32_t uv_handle_type = uv_handle_get_type(uv_handle);
  
  stack[0].ival = uv_handle_type;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__new_idle(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_idle_t* uv_idle = env->new_memory_block(env, stack, sizeof(uv_idle_t));
  
  SPVM__Go__UV__Loop__DATA* uv_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Loop__DATA));
  uv_data->env = env;
  uv_data->stack = stack;
  
  uv_idle->data = uv_data;
  
  SPVM_OBJ* obj_uv_idle = env->new_pointer_object_by_name(env, stack, "Go::UV::Handle::Idle", uv_idle, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_data->uv_handle = obj_uv_idle;
  
  stack[0].oval = obj_uv_idle;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__new_async(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_cb = stack[1].oval;
  
  if (!obj_cb) {
    return env->die(env, stack, "$cb must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  uv_async_t* uv_async = env->new_memory_block(env, stack, sizeof(uv_async_t));
  
  SPVM__Go__UV__Loop__DATA* uv_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Loop__DATA));
  uv_data->env = env;
  uv_data->stack = stack;
  
  uv_async->data = uv_data;
  
  SPVM_OBJ* obj_uv_async = env->new_pointer_object_by_name(env, stack, "Go::UV::Handle::Async", uv_async, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_data->uv_handle = obj_uv_async;
  
  stack[0].oval = obj_uv_async;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__new_timer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_timer_t* uv_timer = env->new_memory_block(env, stack, sizeof(uv_timer_t));
  
  SPVM__Go__UV__Loop__DATA* uv_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Loop__DATA));
  uv_data->env = env;
  uv_data->stack = stack;
  
  uv_timer->data = uv_data;
  
  SPVM_OBJ* obj_uv_timer = env->new_pointer_object_by_name(env, stack, "Go::UV::Handle::Timer", uv_timer, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_data->uv_handle = obj_uv_timer;
  
  stack[0].oval = obj_uv_timer;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__new_write(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_write_t* uv_req_write = env->new_memory_block(env, stack, sizeof(uv_write_t));
  
  SPVM__Go__UV__Loop__DATA* uv_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Loop__DATA));
  uv_data->env = env;
  uv_data->stack = stack;
  
  uv_req_write->data = uv_data;
  
  SPVM_OBJ* obj_uv_write = env->new_pointer_object_by_name(env, stack, "Go::UV::Request::Write", uv_write, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  stack[0].oval = obj_uv_write;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__destroy_write(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_req_write = stack[0].oval;
  
  uv_write_t* uv_req_write = env->get_pointer(env, stack, obj_uv_req_write);
  
  int32_t no_free = env->no_free(env, stack, obj_uv_req_write);
  
  if (!no_free) {
    uv_write_t* uv_req_write = env->get_pointer(env, stack, obj_uv_req_write);
    
    SPVM__Go__UV__Loop__DATA* uv_data = (SPVM__Go__UV__Loop__DATA*)uv_req_write->data;
    
    env->free_memory_block(env, stack, uv_data);
    uv_req_write->data = NULL;
    env->free_memory_block(env, stack, uv_req_write);
    env->set_no_free(env, stack, obj_uv_req_write, 1);
  }
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__new_pipe(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_pipe_t* uv_pipe = env->new_memory_block(env, stack, sizeof(uv_pipe_t));
  
  SPVM__Go__UV__Loop__DATA* uv_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Loop__DATA));
  uv_data->env = env;
  uv_data->stack = stack;
  
  uv_pipe->data = uv_data;
  
  SPVM_OBJ* obj_uv_pipe = env->new_pointer_object_by_name(env, stack, "Go::UV::Handle::Pipe", uv_pipe, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_data->uv_handle = obj_uv_pipe;
  
  stack[0].oval = obj_uv_pipe;
  
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

int32_t SPVM__Go__UV__Loop__handle_pipe_open(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_pipe = stack[0].oval;
  int32_t fd = stack[1].ival;
  
  if (!obj_uv_pipe) {
    return env->die(env, stack, "$uv_pipe must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  uv_pipe_t* uv_pipe = env->get_pointer(env, stack, obj_uv_pipe);
  
  int32_t status = uv_pipe_open(uv_pipe, fd);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_pipe_open failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  return 0;
}

void SPVM__Go__UV__Loop__alloc_cb(uv_handle_t* uv_handle, size_t suggested_size, uv_buf_t* uv_buf) {
  
  int32_t error_id = 0;
  
  SPVM__Go__UV__Loop__DATA* uv_handle_buffer = (SPVM__Go__UV__Loop__DATA*)uv_handle->data;
  
  SPVM_ENV* env = uv_handle_buffer->env;
  SPVM_VALUE* stack = uv_handle_buffer->stack;
  SPVM_OBJ* obj_uv_handle = uv_handle_buffer->uv_handle;
  
  SPVM_OBJ* obj_buffer = env->get_field_object_by_name(env, stack, obj_uv_handle, "read_buffer", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]%s", env->get_exception_chars(env, stack));
    abort();
  }
  const char* buffer = env->get_chars(env, stack, obj_buffer);
  
  int32_t buffer_length = env->get_field_int_by_name(env, stack, obj_uv_handle, "read_buffer_length", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]%s", env->get_exception_chars(env, stack));
    abort();
  }
  
  int32_t buffer_offset = env->get_field_int_by_name(env, stack,obj_uv_handle, "read_buffer_offset", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]%s", env->get_exception_chars(env, stack));
    abort();
  }
  
  uv_buf->base = (char*)buffer + buffer_offset;
  uv_buf->len = buffer_length;
}

int32_t SPVM__Go__UV__Loop__handle_read_start(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_stream = stack[0].oval;
  SPVM_OBJ* obj_buffer = stack[1].oval;
  int32_t buffer_length = stack[2].ival;
  SPVM_OBJ* obj_cb = stack[3].oval;
  int32_t buffer_offset = stack[4].ival;
  
  if (!obj_uv_stream) {
    return env->die(env, stack, "$uv_stream must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_buffer) {
    return env->die(env, stack, "$buffer must be defined.", __func__, FILE_NAME, __LINE__);
  }
  int32_t max_buffer_length = env->length(env, stack, obj_buffer);
  
  if (!(buffer_length > 0)) {
    return env->die(env, stack, "$buffer_length must be a positive number.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(buffer_offset + buffer_length <= max_buffer_length)) {
    return env->die(env, stack, "$buffer_offset + $buffer_length must be less than or equal to the length of $buffer.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_cb) {
    return env->die(env, stack, "$cb must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  env->set_field_object_by_name(env, stack, obj_uv_stream, "read_cb", obj_cb, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  env->set_field_object_by_name(env, stack, obj_uv_stream, "read_buffer", obj_buffer, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  env->set_field_int_by_name(env, stack, obj_uv_stream, "read_buffer_length", buffer_length, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  env->set_field_int_by_name(env, stack, obj_uv_stream, "read_buffer_offset", buffer_offset, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_stream_t* uv_stream = env->get_pointer(env, stack, obj_uv_stream);
  
  int32_t status = uv_read_start(uv_stream, SPVM__Go__UV__Loop__alloc_cb, SPVM__Go__UV__Loop__read_cb);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_read_start failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__handle_write(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_req_write = stack[0].oval;
  SPVM_OBJ* obj_uv_stream = stack[1].oval;
  SPVM_OBJ* obj_buffer = stack[2].oval;
  int32_t buffer_length = stack[3].ival;
  SPVM_OBJ* obj_cb = stack[4].oval;
  int32_t buffer_offset = stack[5].ival;
  
  if (!obj_uv_req_write) {
    return env->die(env, stack, "$uv_req_write must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_uv_stream) {
    return env->die(env, stack, "$uv_stream must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_buffer) {
    return env->die(env, stack, "$buffer must be defined.", __func__, FILE_NAME, __LINE__);
  }
  int32_t max_buffer_length = env->length(env, stack, obj_buffer);
  
  if (!(buffer_length > 0)) {
    return env->die(env, stack, "$buffer_length must be a positive number.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(buffer_offset + buffer_length <= max_buffer_length)) {
    return env->die(env, stack, "$buffer_offset + $buffer_length must be less than or equal to the length of $buffer.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_cb) {
    return env->die(env, stack, "$cb must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  env->set_field_object_by_name(env, stack, obj_uv_stream, "write_cb", obj_cb, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  env->set_field_object_by_name(env, stack, obj_uv_stream, "write_buffer", obj_buffer, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_stream_t* uv_stream = env->get_pointer(env, stack, obj_uv_stream);
  
  const char* buffer = env->get_chars(env, stack, obj_buffer);
  
  uv_write_t* uv_req_write = env->get_pointer(env, stack, obj_uv_req_write);
  
  uv_buf_t uv_buf = {0};
  uv_buf.base = (char*)buffer + buffer_offset;
  uv_buf.len = buffer_length;
  
  SPVM__Go__UV__Loop__DATA* uv_data = (SPVM__Go__UV__Loop__DATA*)uv_req_write->data;
  uv_data->uv_handle = obj_uv_stream;
  int32_t status = uv_write(uv_req_write, uv_stream, &uv_buf, 1, SPVM__Go__UV__Loop__write_cb);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_write failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
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
