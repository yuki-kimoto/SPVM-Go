#include "spvm_native.h"

#include <iostream>
#include <thread>

extern "C" {

static const char* FILE_NAME = "Go/Thread.cpp";

static void thread_handler (SPVM_ENV* env, SPVM_VALUE* stack, void* obj_callback) {
  
  int32_t error_id = 0;
  
  {
    SPVM_VALUE* thread_stack = env->new_stack(env);
    thread_stack[0].oval = obj_callback;
    env->call_instance_method_by_name(env, thread_stack, "", 0, &error_id, __func__, FILE_NAME, __LINE__);
    
    if (error_id) {
      void* obj_exception = env->get_exception(env, thread_stack);
      
      const char* exception = env->get_chars(env, thread_stack, obj_exception);
      
      spvm_warn("%s", exception);
    }
    
    env->free_stack(env, thread_stack);
  }
  
  return;
}

int32_t SPVM__Go__Thread__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_callback = stack[0].oval;
  
  std::thread* nt_thread = (std::thread*)env->new_memory_block(env, stack, sizeof(std::thread));
  
  *nt_thread = std::thread(thread_handler, env, stack, obj_callback);
  
  void* obj_thread = env->new_pointer_object_by_name(env, stack, "Go::Thread", nt_thread, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_thread;
  
  return 0;
}

int32_t SPVM__Go__Thread__joinable(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e;
  
  void* obj_thread = stack[0].oval;
  
  std::thread* nt_thread = (std::thread*)env->get_pointer(env, stack, obj_thread);
  
  int32_t joinable = nt_thread->joinable();
  
  stack[0].ival = joinable;
  
  return 0;
}

int32_t SPVM__Go__Thread__join(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e;
  
  void* obj_thread = stack[0].oval;
  
  std::thread* nt_thread = (std::thread*)env->get_pointer(env, stack, obj_thread);
  
  try {
    nt_thread->join();
  }
  catch (std::exception& cpp_exception){
    env->die(env, stack, "[System Error]join failed:%s", cpp_exception.what(), __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  return 0;
}


int32_t SPVM__Go__Thread__detach(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e;
  
  void* obj_thread = stack[0].oval;
  
  std::thread* nt_thread = (std::thread*)env->get_pointer(env, stack, obj_thread);
  
  try {
    nt_thread->detach();
  }
  catch (std::exception& cpp_exception){
    env->die(env, stack, "[System Error]detach failed:%s", cpp_exception.what(), __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  return 0;
}

int32_t SPVM__Go__Thread__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_thread = stack[0].oval;
  
  std::thread* nt_thread = (std::thread*)env->get_pointer(env, stack, obj_thread);
  
  if (nt_thread->joinable()) {
    nt_thread->detach();
  }
  
  env->free_memory_block(env, stack, nt_thread);
  
  return 0;
}

}
