// Copyright (c) 2026 Yuki Kimoto
// MIT License

#include "spvm_native.h"
#include "uv.h"
#include "spvm_go_uv.h"

static const char* FILE_NAME = "Go/UV/Handle/Pipe.c";

int32_t SPVM__Go__UV__Handle__Pipe__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_pipe_t* uv_pipe = env->new_memory_block(env, stack, sizeof(uv_pipe_t));
  
  SPVM__Go__UV__Handle__HANDLE_DATA* uv_handle_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Handle__HANDLE_DATA));
  uv_handle_data->env = env;
  uv_handle_data->stack = stack;
  
  uv_pipe->data = uv_handle_data;
  
  SPVM_OBJ* obj_uv_pipe = env->new_pointer_object_by_name(env, stack, "Go::UV::Handle::Pipe", uv_pipe, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_handle_data->obj_uv_handle = obj_uv_pipe;
  
  stack[0].oval = obj_uv_pipe;
  
  return 0;
}

int32_t SPVM__Go__UV__Handle__Pipe__open(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

