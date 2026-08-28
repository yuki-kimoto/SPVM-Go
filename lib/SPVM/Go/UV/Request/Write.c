// Copyright (c) 2026 Yuki Kimoto
// MIT License

#include "spvm_native.h"
#include "uv.h"
#include "spvm_go_uv.h"

static const char* FILE_NAME = "Go/UV/Request/Write.c";

void SPVM__Go__UV__Request__Write__write_cb(uv_write_t* uv_handle, int status) {
  
  int32_t error_id = 0;
  
  SPVM__Go__UV__Request__REQ_DATA* uv_req_data = (SPVM__Go__UV__Request__REQ_DATA*)uv_handle->data;
  
  SPVM_ENV* env = uv_req_data->env;
  SPVM_VALUE* stack = uv_req_data->stack;
  SPVM_OBJ* obj_uv_req_write = uv_req_data->obj_uv_req;
  SPVM_OBJ* obj_cb = env->get_field_object_by_name(env, stack, obj_uv_req_write, "write_cb", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[Unexpected Error]Getting 'write_cb' field failed.");
    abort();
  }
  
  assert(obj_cb);
  stack[0].oval = obj_cb;
  stack[1].oval = obj_uv_req_write;
  stack[2].ival = status;
  env->call_instance_method_by_name(env, stack, "", 3, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    spvm_diag("[An exception is converted to a warning in SPVM__Go__UV__Request__Write__write_cb]\n%s", env->get_exception_chars(env, stack));
    return;
  }
  
}

int32_t SPVM__Go__UV__Request__Write__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_write_t* uv_req_write = env->new_memory_block(env, stack, sizeof(uv_write_t));
  
  SPVM__Go__UV__Request__REQ_DATA* uv_req_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Request__REQ_DATA));
  uv_req_data->env = env;
  uv_req_data->stack = stack;
  uv_req_write->data = uv_req_data;
  
  SPVM_OBJ* obj_uv_req_write = env->new_pointer_object_by_name(env, stack, "Go::UV::Request::Write", uv_req_write, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_req_data->obj_uv_req = obj_uv_req_write;
  
  stack[0].oval = obj_uv_req_write;
  
  return 0;
}

int32_t SPVM__Go__UV__Request__Write__write(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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
  
  if (!(buffer_length >= 0)) {
    return env->die(env, stack, "$buffer_length must be a non-negative number.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(buffer_offset + buffer_length <= max_buffer_length)) {
    return env->die(env, stack, "$buffer_offset + $buffer_length must be less than or equal to the length of $buffer.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_cb) {
    return env->die(env, stack, "$cb must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  env->set_field_object_by_name(env, stack, obj_uv_req_write, "write_cb", obj_cb, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  env->set_field_object_by_name(env, stack, obj_uv_req_write, "write_buffer", obj_buffer, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_stream_t* uv_stream = env->get_pointer(env, stack, obj_uv_stream);
  
  const char* buffer = env->get_chars(env, stack, obj_buffer);
  
  uv_write_t* uv_req_write = env->get_pointer(env, stack, obj_uv_req_write);
  
  uv_buf_t uv_buf = {0};
  uv_buf.base = (char*)buffer + buffer_offset;
  uv_buf.len = buffer_length;
  
  int32_t status = uv_write(uv_req_write, uv_stream, &uv_buf, 1, SPVM__Go__UV__Request__Write__write_cb);
  
  if (!(status == 0)) {
    return env->die(env, stack, "uv_write failed. status=%d.", __func__, FILE_NAME, __LINE__, status);
  }
  
  return 0;
}
