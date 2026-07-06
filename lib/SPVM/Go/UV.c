// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>

#include "spvm_native.h"
#include "uv.h"

static const char* FILE_NAME = "Go/UV.c";

void boot_Go__UV(void) {
  
}

int32_t SPVM__Go__UV__my_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

static void uv_test () {
  uv_tcp_t handle;
}

