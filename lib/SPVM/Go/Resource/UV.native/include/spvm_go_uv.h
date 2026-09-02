#ifndef SPVM_GO_UV_H
#define SPVM_GO_UV_H

typedef struct {
  SPVM_ENV* env;
  SPVM_VALUE* stack;
  SPVM_OBJ* obj_uv_handle;
} SPVM__Go__UV__Handle__HANDLE_DATA;

typedef struct {
  SPVM_ENV* env;
  SPVM_VALUE* stack;
  SPVM_OBJ* obj_uv_req;
} SPVM__Go__UV__Request__REQ_DATA;

#endif
