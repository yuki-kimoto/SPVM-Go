// Copyright (c) 2026 Yuki Kimoto
// MIT License

#include "spvm_native.h"
#include "uv.h"
#include "spvm_go_uv.h"

static const char* FILE_NAME = "Go/UV/Request.c";

int32_t SPVM__Go__UV__Request__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_uv_req_write = stack[0].oval;
  
  uv_write_t* uv_req_write = env->get_pointer(env, stack, obj_uv_req_write);
  
  int32_t no_free = env->no_free(env, stack, obj_uv_req_write);
  
  if (!no_free) {
    uv_write_t* uv_req_write = env->get_pointer(env, stack, obj_uv_req_write);
    
    SPVM__Go__UV__Request__REQ_DATA* uv_req_data = (SPVM__Go__UV__Request__REQ_DATA*)uv_req_write->data;
    
    env->free_memory_block(env, stack, uv_req_data);
    uv_req_write->data = NULL;
    env->free_memory_block(env, stack, uv_req_write);
    env->set_no_free(env, stack, obj_uv_req_write, 1);
  }
  
  return 0;
}
