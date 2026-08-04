// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>

#include "spvm_native.h"
#include "coro.h"

static const char* FILE_NAME = "Go/Goroutine.c";

static void goroutine_handler (void* data) {
  
  SPVM_OBJ* obj_self = (SPVM_OBJ*)data;
  
  int32_t error_id = 0;
  
  void** pointer_items = (void**)SPVM_NATIVE_GET_POINTER(obj_self);
  
  SPVM_ENV* env = pointer_items[2];
  
  SPVM_VALUE* stack = pointer_items[3];
  
  SPVM_OBJ* obj_task = env->get_field_object_by_name(env, stack, obj_self, "task", &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  void* method = env->get_instance_method(env, stack, obj_task, "");
  
  stack[0].oval = obj_task;
  error_id = env->call_method(env, stack, method, 1, __func__, FILE_NAME, __LINE__);
  
  if (error_id) {
    // Reconstruct the full exception message including stack trace.
    // The level 0 means the trace starts from the origin of the exception.
    
    int32_t scope_id = env->enter_scope(env, stack);
    
    SPVM_OBJ* obj_full_exception_message = env->build_exception_message(env, stack, 0);
    
    fprintf(env->api->runtime->get_spvm_stderr(env->runtime), "[An exception thrown in a goroutine is converted to a warning]\n");
    
    // Print the full exception message with stack trace.
    env->print_stderr(env, stack, obj_full_exception_message);
    
    env->leave_scope(env, stack, scope_id);
    
    fprintf(env->api->runtime->get_spvm_stderr(env->runtime), "\n");
  }
  
  SPVM_OBJ* obj_return_back = env->get_field_object_by_name(env, stack, obj_self, "return_back", &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  coro_context* goroutine_context = pointer_items[0];
  
  void** goroutine_context_return_back_pointer_items = env->get_pointer(env, stack, obj_return_back);
  
  coro_context* goroutine_context_return_back = goroutine_context_return_back_pointer_items[0];
  assert(error_id == 0);
  
  env->set_field_byte_by_name(env, stack, obj_self, "finished", 1, &error_id, __func__, FILE_NAME, __LINE__);
  assert(error_id == 0);
  
  coro_transfer(goroutine_context, goroutine_context_return_back);
  
  assert(0);
}

int32_t SPVM__Go__Goroutine__init_goroutine(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_self = stack[0].oval;
  
  SPVM_OBJ* obj_task = env->get_field_object_by_name(env, stack, obj_self, "task", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) return error_id;
  
  coro_context* goroutine_context = env->new_memory_block(env, stack, sizeof(coro_context));
  struct coro_stack* goroutine_stack = NULL;
  if (obj_task) {
    goroutine_stack = env->new_memory_block(env, stack, sizeof(struct coro_stack));
    
    if (!coro_stack_alloc(goroutine_stack, 0)) {
      return env->die(env, stack, "coro_stack_alloc failed.", __func__, FILE_NAME, __LINE__);
    }
    
    coro_create(goroutine_context, goroutine_handler, obj_self, goroutine_stack->sptr,  goroutine_stack->ssze);
  }
  else {
    coro_create(goroutine_context, NULL, NULL, NULL, 0);
  }
  
  void** pointer_items = env->new_memory_block(env, stack, sizeof(void*) * 4);
  
  SPVM_VALUE* goroutine_spvm_stack = env->new_stack(env);
  
  pointer_items[0] = goroutine_context;
  pointer_items[1] = goroutine_stack;
  pointer_items[2] = env;
  pointer_items[3] = goroutine_spvm_stack;
  
  env->set_pointer(env, stack, obj_self, pointer_items);
  
  return 0;
}

int32_t SPVM__Go__Goroutine__transfer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_goroutine_from = stack[0].oval;
  
  if (!obj_goroutine_from) {
    return env->die(env, stack, "$from must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void** goroutine_from_pointer_items = env->get_pointer(env, stack, obj_goroutine_from);
  
  coro_context* goroutine_context_from = goroutine_from_pointer_items[0];
  
  SPVM_OBJ* obj_goroutine_to = stack[1].oval;
  
  if (!obj_goroutine_to) {
    return env->die(env, stack, "$to must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void** goroutine_to_pointer_items = env->get_pointer(env, stack, obj_goroutine_to);
  
  coro_context* goroutine_context_to = goroutine_to_pointer_items[0];
  
  coro_transfer(goroutine_context_from, goroutine_context_to);
  
  return 0;
}

int32_t SPVM__Go__Goroutine__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_self = stack[0].oval;
  
  void** pointer_items = env->get_pointer(env, stack, obj_self);
  
  coro_context* goroutine_context = pointer_items[0];
  
  struct coro_stack* goroutine_stack = pointer_items[1];
  
  SPVM_VALUE* goroutine_spvm_stack = pointer_items[3];
  
  env->free_stack(env, goroutine_spvm_stack);
  
  if (goroutine_stack) {
    coro_destroy(goroutine_context);
    
    coro_stack_free(goroutine_stack);
    
    env->free_memory_block(env, stack, goroutine_stack);
  }
  
  env->free_memory_block(env, stack, goroutine_context);
  
  env->free_memory_block(env, stack, pointer_items);
  
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#ifdef _WIN32
  #include <windows.h>
  #include <io.h>
#else
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <fcntl.h>
#endif

int32_t SPVM__Go__Goroutine___pipepair(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t* read_fd_ref = stack[0].iref;
  if (!read_fd_ref) {
    return env->die(env, stack, "$read_fd_ref must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t* write_fd_ref = stack[1].iref;
  if (!write_fd_ref) {
    return env->die(env, stack, "$write_fd_ref must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t non_blocking = stack[2].ival;
  
#ifdef _WIN32
  // Generate secure GUID for named pipe
  char pipename[128];
  GUID guid;
  if (CoCreateGuid(&guid) != S_OK) {
    return env->die(env, stack, "CoCreateGuid failed.", __func__, FILE_NAME, __LINE__);
  }
  
  snprintf(
    pipename,
    sizeof(pipename),
    "\\\\.\\pipe\\spvm-pipe-%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
    guid.Data1, guid.Data2, guid.Data3,
    guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
    guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]
  );
  
  // Enable handle inheritance
  SECURITY_ATTRIBUTES sa;
  sa.nLength = sizeof(SECURITY_ATTRIBUTES);
  sa.lpSecurityDescriptor = NULL;
  sa.bInheritHandle = TRUE;
  
  DWORD open_mode = PIPE_ACCESS_DUPLEX | FILE_FLAG_FIRST_PIPE_INSTANCE;
  DWORD pipe_mode = PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT;
  DWORD file_flags = 0;
  if (non_blocking) {
    file_flags |= FILE_FLAG_OVERLAPPED;
  }
  
  HANDLE hRead = CreateNamedPipeA(
    pipename,
    open_mode,
    pipe_mode,
    1,
    4096,
    4096,
    0,
    &sa
  );
  if (hRead == INVALID_HANDLE_VALUE) {
    return env->die(env, stack, "CreateNamedPipe failed.", __func__, FILE_NAME, __LINE__);
  }
  
  HANDLE hWrite = CreateFileA(
    pipename,
    GENERIC_WRITE,
    0,
    &sa,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL | file_flags,
    NULL
  );
  if (hWrite == INVALID_HANDLE_VALUE) {
    CloseHandle(hRead);
    return env->die(env, stack, "CreateFile for named pipe failed.", __func__, FILE_NAME, __LINE__);
  }
  
  *read_fd_ref = _open_osfhandle((intptr_t)hRead, 0);
  *write_fd_ref = _open_osfhandle((intptr_t)hWrite, 0);
#else
  // Create socketpair for Unix systems
  int fds[2];
  int type = SOCK_STREAM;
  if (socketpair(AF_UNIX, type, 0, fds) < 0) {
    return env->die(env, stack, "socketpair failed.", __func__, FILE_NAME, __LINE__);
  }
  
  if (non_blocking) {
    int flags = fcntl(fds[0], F_GETFL, 0);
    fcntl(fds[0], F_SETFL, flags | O_NONBLOCK);
    flags = fcntl(fds[1], F_GETFL, 0);
    fcntl(fds[1], F_SETFL, flags | O_NONBLOCK);
  }
  
  *read_fd_ref = fds[0];
  *write_fd_ref = fds[1];
#endif

  return 0;
}
