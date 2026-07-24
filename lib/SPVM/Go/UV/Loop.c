// Copyright (c) 2026 Yuki Kimoto
// MIT License

#include "spvm_native.h"
#include "uv.h"

static const char* FILE_NAME = "Go/UV/Loop.c";

typedef struct {
  SPVM_ENV* env;
  SPVM_VALUE* stack;
  SPVM_OBJ* obj_uv_handle;
  uv_handle_t* related_uv_handle;
} SPVM__Go__UV__Loop__HANDLE_DATA;

int32_t SPVM__Go__UV__Loop__default_loop(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_loop_t* uv_loop = uv_default_loop();
  
  SPVM_OBJ* obj_uv_loop = env->new_pointer_object_by_name(env, stack, "Go::UV::Loop", uv_loop, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  stack[0].oval = obj_uv_loop;
  
  return 0;
}

static void SPVM__Go__UV__Loop__close_cb(uv_handle_t* uv_handle) {
  
  int32_t error_id = 0;
  
  SPVM__Go__UV__Loop__HANDLE_DATA* uv_handle_data = (SPVM__Go__UV__Loop__HANDLE_DATA*)uv_handle->data;
  
  SPVM_ENV* env = uv_handle_data->env;
  SPVM_VALUE* stack = uv_handle_data->stack;
  SPVM_OBJ* obj_uv_handle = uv_handle_data->obj_uv_handle;
  SPVM_OBJ* obj_cb = env->get_field_object_by_name(env, stack, obj_uv_handle, "close_cb", &error_id, __func__, FILE_NAME, __LINE__);
  
  if (obj_cb) {
    stack[0].oval = obj_cb;
    stack[1].oval = obj_uv_handle;
    env->call_instance_method_by_name(env, stack, "", 2, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) {
      spvm_diag("[Unexpected Error]%s", env->get_exception_chars(env, stack));
      abort();
    }
  }
  
  SPVM_OBJ* obj_uv_loop = env->get_field_object_by_name(env, stack, obj_uv_handle, "loop", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]%s", env->get_exception_chars(env, stack));
    abort();
  }
  
  stack[0].oval = obj_uv_loop;
  stack[1].oval = obj_uv_handle;
  env->call_instance_method_by_name(env, stack, "delete_uv_handle", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]%s", env->get_exception_chars(env, stack));
    abort();
  }
}

static void SPVM__Go__UV__Loop__handle_cb(uv_handle_t* uv_handle) {
  
  int32_t error_id = 0;
  
  SPVM__Go__UV__Loop__HANDLE_DATA* uv_handle_data = (SPVM__Go__UV__Loop__HANDLE_DATA*)uv_handle->data;
  
  SPVM_ENV* env = uv_handle_data->env;
  SPVM_VALUE* stack = uv_handle_data->stack;
  SPVM_OBJ* obj_uv_handle = uv_handle_data->obj_uv_handle;
  SPVM_OBJ* obj_cb = env->get_field_object_by_name(env, stack, obj_uv_handle, "cb", &error_id, __func__, FILE_NAME, __LINE__);
  
  assert(obj_cb);
  stack[0].oval = obj_cb;
  stack[1].oval = obj_uv_handle;
  env->call_instance_method_by_name(env, stack, "", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (!(error_id == 0)) {
    spvm_diag("[Unexcepted Error]Callback 'cb' failed.");
    abort();
  }
}

static void SPVM__Go__UV__Loop__idle_cb(uv_idle_t* uv_idle) {
  
  SPVM__Go__UV__Loop__handle_cb((uv_handle_t*)uv_idle);
}

static void SPVM__Go__UV__Loop__async_cb(uv_async_t* uv_async) {
  SPVM__Go__UV__Loop__handle_cb((uv_handle_t*)uv_async);
}

static void SPVM__Go__UV__Loop__timer_cb(uv_timer_t* uv_timer) {
  SPVM__Go__UV__Loop__handle_cb((uv_handle_t*)uv_timer);
}

static void SPVM__Go__UV__Loop__poll_cb(uv_poll_t* uv_poll, int status, int event) {
  
  SPVM__Go__UV__Loop__handle_cb((uv_handle_t*)uv_poll);
}

void SPVM__Go__UV__Loop__read_cb(uv_stream_t* uv_stream, ssize_t nread, const uv_buf_t* buf) {
  
  SPVM__Go__UV__Loop__handle_cb((uv_handle_t*)uv_stream);
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
  
  env->set_field_object_by_name(env, stack, obj_uv_async, "cb", obj_cb, &error_id, __func__, FILE_NAME, __LINE__);
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
  
  SPVM__Go__UV__Loop__HANDLE_DATA* uv_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Loop__HANDLE_DATA));
  uv_handle_data->env = env;
  uv_handle_data->stack = stack;
  
  uv_poll->data = uv_handle_data;
  
  SPVM_OBJ* obj_uv_poll = env->new_pointer_object_by_name(env, stack, "Go::UV::Handle::Poll", uv_poll, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_handle_data->obj_uv_handle = obj_uv_poll;
  
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
  SPVM__Go__UV__Loop__HANDLE_DATA* uv_idle_data = uv_idle->data;
  
  env->set_field_object_by_name(env, stack, obj_uv_idle, "cb", obj_cb, &error_id, __func__, FILE_NAME, __LINE__);
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
  
  env->set_field_object_by_name(env, stack, obj_uv_timer, "cb", obj_cb, &error_id, __func__, FILE_NAME, __LINE__);
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
  
  env->set_field_object_by_name(env, stack, obj_uv_poll, "cb", obj_cb, &error_id, __func__, FILE_NAME, __LINE__);
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
  
  uv_close(uv_handle, SPVM__Go__UV__Loop__close_cb);
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__handle_free(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_uv_handle = stack[0].oval;
  
  int32_t no_free = env->no_free(env, stack, obj_uv_handle);
  
  if (!no_free) {
    uv_handle_t* uv_handle = env->get_pointer(env, stack, obj_uv_handle);
    
    SPVM__Go__UV__Loop__HANDLE_DATA* uv_handle_data = (SPVM__Go__UV__Loop__HANDLE_DATA*)uv_handle->data;
    
    env->free_memory_block(env, stack, uv_handle_data);
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
  
  SPVM__Go__UV__Loop__HANDLE_DATA* uv_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Loop__HANDLE_DATA));
  uv_handle_data->env = env;
  uv_handle_data->stack = stack;
  
  uv_idle->data = uv_handle_data;
  
  SPVM_OBJ* obj_uv_idle = env->new_pointer_object_by_name(env, stack, "Go::UV::Handle::Idle", uv_idle, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_handle_data->obj_uv_handle = obj_uv_idle;
  
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
  
  SPVM__Go__UV__Loop__HANDLE_DATA* uv_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Loop__HANDLE_DATA));
  uv_handle_data->env = env;
  uv_handle_data->stack = stack;
  
  uv_async->data = uv_handle_data;
  
  SPVM_OBJ* obj_uv_async = env->new_pointer_object_by_name(env, stack, "Go::UV::Handle::Async", uv_async, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_handle_data->obj_uv_handle = obj_uv_async;
  
  stack[0].oval = obj_uv_async;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__new_timer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_timer_t* uv_timer = env->new_memory_block(env, stack, sizeof(uv_timer_t));
  
  SPVM__Go__UV__Loop__HANDLE_DATA* uv_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Loop__HANDLE_DATA));
  uv_handle_data->env = env;
  uv_handle_data->stack = stack;
  
  uv_timer->data = uv_handle_data;
  
  SPVM_OBJ* obj_uv_timer = env->new_pointer_object_by_name(env, stack, "Go::UV::Handle::Timer", uv_timer, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_handle_data->obj_uv_handle = obj_uv_timer;
  
  stack[0].oval = obj_uv_timer;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__new_write(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_write_t* uv_write = env->new_memory_block(env, stack, sizeof(uv_write_t));
  
  SPVM_OBJ* obj_uv_write = env->new_pointer_object_by_name(env, stack, "Go::UV::Handle::Write", uv_write, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  stack[0].oval = obj_uv_write;
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__destroy_write(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_write = stack[0].oval;
  
  uv_write_t* uv_write = env->get_pointer(env, stack, obj_uv_write);
  
  env->free_memory_block(env, stack, uv_write);
  
  return 0;
}

int32_t SPVM__Go__UV__Loop__new_pipe(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_pipe_t* uv_pipe = env->new_memory_block(env, stack, sizeof(uv_pipe_t));
  
  SPVM__Go__UV__Loop__HANDLE_DATA* uv_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Loop__HANDLE_DATA));
  uv_handle_data->env = env;
  uv_handle_data->stack = stack;
  
  uv_pipe->data = uv_handle_data;
  
  SPVM_OBJ* obj_uv_pipe = env->new_pointer_object_by_name(env, stack, "Go::UV::Handle::Pipe", uv_pipe, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_handle_data->obj_uv_handle = obj_uv_pipe;
  
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

void SPVM__Go__UV__Loop__alloc_cb(uv_handle_t* uv_handle, size_t suggested_size, uv_buf_t* buf) {
  
  int32_t error_id = 0;
  
  buf->base = NULL;
  buf->len = 0;
  
  SPVM__Go__UV__Loop__HANDLE_DATA* uv_handle_buffer = (SPVM__Go__UV__Loop__HANDLE_DATA*)uv_handle->data;
  
  SPVM_ENV* env = uv_handle_buffer->env;
  SPVM_VALUE* stack = uv_handle_buffer->stack;
  SPVM_OBJ* obj_uv_handle = uv_handle_buffer->obj_uv_handle;
  
  SPVM_OBJ* obj_buffer = env->get_field_object_by_name(env, stack, obj_uv_handle, "buffer", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]%s", env->get_exception_chars(env, stack));
    abort();
  }
  const char* buffer = env->get_chars(env, stack, obj_buffer);
  
  int32_t buffer_length = env->get_field_int_by_name(env, stack, obj_uv_handle, "buffer_length", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]%s", env->get_exception_chars(env, stack));
    abort();
  }
  
  buf->base = (char*)buffer;
  buf->len = buffer_length;
}

int32_t SPVM__Go__UV__Loop__handle_read_start(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_pipe = stack[0].oval;
  SPVM_OBJ* obj_buffer = stack[1].oval;
  int32_t buffer_length = stack[2].oval;
  SPVM_OBJ* obj_cb = stack[3].oval;
  
  if (!obj_buffer) {
    return env->die(env, stack, "$buffer must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_cb) {
    return env->die(env, stack, "$cb must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void* buffer_chars = env->get_chars(env, stack, obj_buffer);
  int32_t buffer_len = env->length(env, stack, obj_buffer);
  
  env->set_field_object_by_name(env, stack, obj_uv_pipe, "cb", obj_cb, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  env->set_field_object_by_name(env, stack, obj_uv_pipe, "buffer", obj_buffer, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  env->set_field_int_by_name(env, stack, obj_uv_pipe, "buffer_length", buffer_length, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_pipe_t* uv_pipe = env->get_pointer(env, stack, obj_uv_pipe);
  
  int32_t status = uv_read_start((uv_stream_t*)uv_pipe, SPVM__Go__UV__Loop__alloc_cb, SPVM__Go__UV__Loop__read_cb);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_read_start failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  return 0;
}
