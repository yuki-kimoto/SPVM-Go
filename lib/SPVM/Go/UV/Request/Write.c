// Copyright (c) 2026 Yuki Kimoto
// MIT License

#include "spvm_native.h"
#include "uv.h"

static const char* FILE_NAME = "Go/UV/Request/Write.c";

typedef struct {
  SPVM_ENV* env;
  SPVM_VALUE* stack;
  SPVM_OBJ* obj_uv_req;
} SPVM__Go__UV__Loop__REQ_DATA;

int32_t SPVM__Go__UV__Request__Write__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  uv_write_t* uv_req_write = env->new_memory_block(env, stack, sizeof(uv_write_t));
  
  SPVM__Go__UV__Loop__REQ_DATA* uv_req_data = env->new_memory_block(env, stack, sizeof(SPVM__Go__UV__Loop__REQ_DATA));
  uv_req_data->env = env;
  uv_req_data->stack = stack;
  uv_req_write->data = uv_req_data;
  
  SPVM_OBJ* obj_uv_req_write = env->new_pointer_object_by_name(env, stack, "Go::UV::Request::Write", uv_req_write, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  uv_req_data->obj_uv_req = obj_uv_req_write;
  
  stack[0].oval = obj_uv_req_write;
  
  return 0;
}

int32_t SPVM__Go__UV__Request__Write__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_req_write = stack[0].oval;
  
  uv_write_t* uv_req_write = env->get_pointer(env, stack, obj_uv_req_write);
  
  int32_t no_free = env->no_free(env, stack, obj_uv_req_write);
  
  if (!no_free) {
    uv_write_t* uv_req_write = env->get_pointer(env, stack, obj_uv_req_write);
    
    SPVM__Go__UV__Loop__REQ_DATA* uv_req_data = (SPVM__Go__UV__Loop__REQ_DATA*)uv_req_write->data;
    
    env->free_memory_block(env, stack, uv_req_data);
    uv_req_write->data = NULL;
    env->free_memory_block(env, stack, uv_req_write);
    env->set_no_free(env, stack, obj_uv_req_write, 1);
  }
  
  return 0;
}
