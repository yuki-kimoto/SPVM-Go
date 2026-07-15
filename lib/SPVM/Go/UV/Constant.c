#include "spvm_native.h"

static const char* FILE_NAME = "Go/UV/Constant.c";

int32_t SPVM__Go__UV__Constant__UV_VERSION_MAJOR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_VERSION_MAJOR
  stack[0].ival = (int32_t)UV_VERSION_MAJOR;
  return 0;
#else
  env->die(env, stack, "UV_VERSION_MAJOR is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_VERSION_MINOR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_VERSION_MINOR
  stack[0].ival = (int32_t)UV_VERSION_MINOR;
  return 0;
#else
  env->die(env, stack, "UV_VERSION_MINOR is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_VERSION_PATCH(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_VERSION_PATCH
  stack[0].ival = (int32_t)UV_VERSION_PATCH;
  return 0;
#else
  env->die(env, stack, "UV_VERSION_PATCH is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_VERSION_IS_RELEASE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_VERSION_IS_RELEASE
  stack[0].ival = (int32_t)UV_VERSION_IS_RELEASE;
  return 0;
#else
  env->die(env, stack, "UV_VERSION_IS_RELEASE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_VERSION_HEX(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_VERSION_HEX
  stack[0].ival = (int32_t)UV_VERSION_HEX;
  return 0;
#else
  env->die(env, stack, "UV_VERSION_HEX is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_VERSION_SUFFIX(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_VERSION_SUFFIX
  stack[0].sval = env->new_string_nolen(env, stack, UV_VERSION_SUFFIX);
  return 0;
#else
  env->die(env, stack, "UV_VERSION_SUFFIX is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_E2BIG(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_E2BIG
  stack[0].ival = (int32_t)UV_E2BIG;
  return 0;
#else
  env->die(env, stack, "UV_E2BIG is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EACCES(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EACCES
  stack[0].ival = (int32_t)UV_EACCES;
  return 0;
#else
  env->die(env, stack, "UV_EACCES is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EADDRINUSE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EADDRINUSE
  stack[0].ival = (int32_t)UV_EADDRINUSE;
  return 0;
#else
  env->die(env, stack, "UV_EADDRINUSE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EADDRNOTAVAIL(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EADDRNOTAVAIL
  stack[0].ival = (int32_t)UV_EADDRNOTAVAIL;
  return 0;
#else
  env->die(env, stack, "UV_EADDRNOTAVAIL is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAFNOSUPPORT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAFNOSUPPORT
  stack[0].ival = (int32_t)UV_EAFNOSUPPORT;
  return 0;
#else
  env->die(env, stack, "UV_EAFNOSUPPORT is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAGAIN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAGAIN
  stack[0].ival = (int32_t)UV_EAGAIN;
  return 0;
#else
  env->die(env, stack, "UV_EAGAIN is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_ADDRFAMILY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_ADDRFAMILY
  stack[0].ival = (int32_t)UV_EAI_ADDRFAMILY;
  return 0;
#else
  env->die(env, stack, "UV_EAI_ADDRFAMILY is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_AGAIN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_AGAIN
  stack[0].ival = (int32_t)UV_EAI_AGAIN;
  return 0;
#else
  env->die(env, stack, "UV_EAI_AGAIN is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_BADFLAGS(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_BADFLAGS
  stack[0].ival = (int32_t)UV_EAI_BADFLAGS;
  return 0;
#else
  env->die(env, stack, "UV_EAI_BADFLAGS is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_BADHINTS(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_BADHINTS
  stack[0].ival = (int32_t)UV_EAI_BADHINTS;
  return 0;
#else
  env->die(env, stack, "UV_EAI_BADHINTS is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_CANCELED(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_CANCELED
  stack[0].ival = (int32_t)UV_EAI_CANCELED;
  return 0;
#else
  env->die(env, stack, "UV_EAI_CANCELED is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_FAIL(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_FAIL
  stack[0].ival = (int32_t)UV_EAI_FAIL;
  return 0;
#else
  env->die(env, stack, "UV_EAI_FAIL is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_FAMILY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_FAMILY
  stack[0].ival = (int32_t)UV_EAI_FAMILY;
  return 0;
#else
  env->die(env, stack, "UV_EAI_FAMILY is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_MEMORY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_MEMORY
  stack[0].ival = (int32_t)UV_EAI_MEMORY;
  return 0;
#else
  env->die(env, stack, "UV_EAI_MEMORY is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_NODATA(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_NODATA
  stack[0].ival = (int32_t)UV_EAI_NODATA;
  return 0;
#else
  env->die(env, stack, "UV_EAI_NODATA is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_NONAME(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_NONAME
  stack[0].ival = (int32_t)UV_EAI_NONAME;
  return 0;
#else
  env->die(env, stack, "UV_EAI_NONAME is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_OVERFLOW(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_OVERFLOW
  stack[0].ival = (int32_t)UV_EAI_OVERFLOW;
  return 0;
#else
  env->die(env, stack, "UV_EAI_OVERFLOW is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_PROTOCOL(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_PROTOCOL
  stack[0].ival = (int32_t)UV_EAI_PROTOCOL;
  return 0;
#else
  env->die(env, stack, "UV_EAI_PROTOCOL is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_SERVICE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_SERVICE
  stack[0].ival = (int32_t)UV_EAI_SERVICE;
  return 0;
#else
  env->die(env, stack, "UV_EAI_SERVICE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EAI_SOCKTYPE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EAI_SOCKTYPE
  stack[0].ival = (int32_t)UV_EAI_SOCKTYPE;
  return 0;
#else
  env->die(env, stack, "UV_EAI_SOCKTYPE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EALREADY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EALREADY
  stack[0].ival = (int32_t)UV_EALREADY;
  return 0;
#else
  env->die(env, stack, "UV_EALREADY is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EBADF(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EBADF
  stack[0].ival = (int32_t)UV_EBADF;
  return 0;
#else
  env->die(env, stack, "UV_EBADF is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EBUSY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EBUSY
  stack[0].ival = (int32_t)UV_EBUSY;
  return 0;
#else
  env->die(env, stack, "UV_EBUSY is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ECANCELED(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ECANCELED
  stack[0].ival = (int32_t)UV_ECANCELED;
  return 0;
#else
  env->die(env, stack, "UV_ECANCELED is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ECHARSET(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ECHARSET
  stack[0].ival = (int32_t)UV_ECHARSET;
  return 0;
#else
  env->die(env, stack, "UV_ECHARSET is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ECONNABORTED(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ECONNABORTED
  stack[0].ival = (int32_t)UV_ECONNABORTED;
  return 0;
#else
  env->die(env, stack, "UV_ECONNABORTED is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ECONNREFUSED(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ECONNREFUSED
  stack[0].ival = (int32_t)UV_ECONNREFUSED;
  return 0;
#else
  env->die(env, stack, "UV_ECONNREFUSED is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ECONNRESET(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ECONNRESET
  stack[0].ival = (int32_t)UV_ECONNRESET;
  return 0;
#else
  env->die(env, stack, "UV_ECONNRESET is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EDESTADDRREQ(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EDESTADDRREQ
  stack[0].ival = (int32_t)UV_EDESTADDRREQ;
  return 0;
#else
  env->die(env, stack, "UV_EDESTADDRREQ is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EEXIST(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EEXIST
  stack[0].ival = (int32_t)UV_EEXIST;
  return 0;
#else
  env->die(env, stack, "UV_EEXIST is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EFAULT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EFAULT
  stack[0].ival = (int32_t)UV_EFAULT;
  return 0;
#else
  env->die(env, stack, "UV_EFAULT is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EFBIG(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EFBIG
  stack[0].ival = (int32_t)UV_EFBIG;
  return 0;
#else
  env->die(env, stack, "UV_EFBIG is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EHOSTUNREACH(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EHOSTUNREACH
  stack[0].ival = (int32_t)UV_EHOSTUNREACH;
  return 0;
#else
  env->die(env, stack, "UV_EHOSTUNREACH is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EINTR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EINTR
  stack[0].ival = (int32_t)UV_EINTR;
  return 0;
#else
  env->die(env, stack, "UV_EINTR is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EINVAL(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EINVAL
  stack[0].ival = (int32_t)UV_EINVAL;
  return 0;
#else
  env->die(env, stack, "UV_EINVAL is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EIO(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EIO
  stack[0].ival = (int32_t)UV_EIO;
  return 0;
#else
  env->die(env, stack, "UV_EIO is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EISCONN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EISCONN
  stack[0].ival = (int32_t)UV_EISCONN;
  return 0;
#else
  env->die(env, stack, "UV_EISCONN is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EISDIR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EISDIR
  stack[0].ival = (int32_t)UV_EISDIR;
  return 0;
#else
  env->die(env, stack, "UV_EISDIR is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ELOOP(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ELOOP
  stack[0].ival = (int32_t)UV_ELOOP;
  return 0;
#else
  env->die(env, stack, "UV_ELOOP is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EMFILE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EMFILE
  stack[0].ival = (int32_t)UV_EMFILE;
  return 0;
#else
  env->die(env, stack, "UV_EMFILE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EMSGSIZE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EMSGSIZE
  stack[0].ival = (int32_t)UV_EMSGSIZE;
  return 0;
#else
  env->die(env, stack, "UV_EMSGSIZE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENAMETOOLONG(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENAMETOOLONG
  stack[0].ival = (int32_t)UV_ENAMETOOLONG;
  return 0;
#else
  env->die(env, stack, "UV_ENAMETOOLONG is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENETDOWN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENETDOWN
  stack[0].ival = (int32_t)UV_ENETDOWN;
  return 0;
#else
  env->die(env, stack, "UV_ENETDOWN is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENETUNREACH(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENETUNREACH
  stack[0].ival = (int32_t)UV_ENETUNREACH;
  return 0;
#else
  env->die(env, stack, "UV_ENETUNREACH is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENFILE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENFILE
  stack[0].ival = (int32_t)UV_ENFILE;
  return 0;
#else
  env->die(env, stack, "UV_ENFILE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENOBUFS(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENOBUFS
  stack[0].ival = (int32_t)UV_ENOBUFS;
  return 0;
#else
  env->die(env, stack, "UV_ENOBUFS is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENODEV(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENODEV
  stack[0].ival = (int32_t)UV_ENODEV;
  return 0;
#else
  env->die(env, stack, "UV_ENODEV is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENOENT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENOENT
  stack[0].ival = (int32_t)UV_ENOENT;
  return 0;
#else
  env->die(env, stack, "UV_ENOENT is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENOMEM(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENOMEM
  stack[0].ival = (int32_t)UV_ENOMEM;
  return 0;
#else
  env->die(env, stack, "UV_ENOMEM is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENONET(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENONET
  stack[0].ival = (int32_t)UV_ENONET;
  return 0;
#else
  env->die(env, stack, "UV_ENONET is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENOPROTOOPT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENOPROTOOPT
  stack[0].ival = (int32_t)UV_ENOPROTOOPT;
  return 0;
#else
  env->die(env, stack, "UV_ENOPROTOOPT is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENOSPC(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENOSPC
  stack[0].ival = (int32_t)UV_ENOSPC;
  return 0;
#else
  env->die(env, stack, "UV_ENOSPC is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENOSYS(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENOSYS
  stack[0].ival = (int32_t)UV_ENOSYS;
  return 0;
#else
  env->die(env, stack, "UV_ENOSYS is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENOTCONN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENOTCONN
  stack[0].ival = (int32_t)UV_ENOTCONN;
  return 0;
#else
  env->die(env, stack, "UV_ENOTCONN is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENOTDIR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENOTDIR
  stack[0].ival = (int32_t)UV_ENOTDIR;
  return 0;
#else
  env->die(env, stack, "UV_ENOTDIR is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENOTEMPTY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENOTEMPTY
  stack[0].ival = (int32_t)UV_ENOTEMPTY;
  return 0;
#else
  env->die(env, stack, "UV_ENOTEMPTY is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENOTSOCK(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENOTSOCK
  stack[0].ival = (int32_t)UV_ENOTSOCK;
  return 0;
#else
  env->die(env, stack, "UV_ENOTSOCK is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENOTSUP(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENOTSUP
  stack[0].ival = (int32_t)UV_ENOTSUP;
  return 0;
#else
  env->die(env, stack, "UV_ENOTSUP is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EPERM(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EPERM
  stack[0].ival = (int32_t)UV_EPERM;
  return 0;
#else
  env->die(env, stack, "UV_EPERM is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EPIPE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EPIPE
  stack[0].ival = (int32_t)UV_EPIPE;
  return 0;
#else
  env->die(env, stack, "UV_EPIPE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EPROTO(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EPROTO
  stack[0].ival = (int32_t)UV_EPROTO;
  return 0;
#else
  env->die(env, stack, "UV_EPROTO is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EPROTONOSUPPORT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EPROTONOSUPPORT
  stack[0].ival = (int32_t)UV_EPROTONOSUPPORT;
  return 0;
#else
  env->die(env, stack, "UV_EPROTONOSUPPORT is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EPROTOTYPE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EPROTOTYPE
  stack[0].ival = (int32_t)UV_EPROTOTYPE;
  return 0;
#else
  env->die(env, stack, "UV_EPROTOTYPE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ERANGE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ERANGE
  stack[0].ival = (int32_t)UV_ERANGE;
  return 0;
#else
  env->die(env, stack, "UV_ERANGE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EROFS(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EROFS
  stack[0].ival = (int32_t)UV_EROFS;
  return 0;
#else
  env->die(env, stack, "UV_EROFS is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ESHUTDOWN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ESHUTDOWN
  stack[0].ival = (int32_t)UV_ESHUTDOWN;
  return 0;
#else
  env->die(env, stack, "UV_ESHUTDOWN is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ESPIPE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ESPIPE
  stack[0].ival = (int32_t)UV_ESPIPE;
  return 0;
#else
  env->die(env, stack, "UV_ESPIPE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ESRCH(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ESRCH
  stack[0].ival = (int32_t)UV_ESRCH;
  return 0;
#else
  env->die(env, stack, "UV_ESRCH is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ETIMEDOUT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ETIMEDOUT
  stack[0].ival = (int32_t)UV_ETIMEDOUT;
  return 0;
#else
  env->die(env, stack, "UV_ETIMEDOUT is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ETXTBSY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ETXTBSY
  stack[0].ival = (int32_t)UV_ETXTBSY;
  return 0;
#else
  env->die(env, stack, "UV_ETXTBSY is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EXDEV(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EXDEV
  stack[0].ival = (int32_t)UV_EXDEV;
  return 0;
#else
  env->die(env, stack, "UV_EXDEV is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_UNKNOWN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_UNKNOWN
  stack[0].ival = (int32_t)UV_UNKNOWN;
  return 0;
#else
  env->die(env, stack, "UV_UNKNOWN is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EOF(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EOF
  stack[0].ival = (int32_t)UV_EOF;
  return 0;
#else
  env->die(env, stack, "UV_EOF is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ENXIO(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ENXIO
  stack[0].ival = (int32_t)UV_ENXIO;
  return 0;
#else
  env->die(env, stack, "UV_ENXIO is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_EMLINK(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_EMLINK
  stack[0].ival = (int32_t)UV_EMLINK;
  return 0;
#else
  env->die(env, stack, "UV_EMLINK is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_ASYNC(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_ASYNC
  stack[0].ival = (int32_t)UV_ASYNC;
  return 0;
#else
  env->die(env, stack, "UV_ASYNC is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_CHECK(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_CHECK
  stack[0].ival = (int32_t)UV_CHECK;
  return 0;
#else
  env->die(env, stack, "UV_CHECK is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_FS_EVENT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_FS_EVENT
  stack[0].ival = (int32_t)UV_FS_EVENT;
  return 0;
#else
  env->die(env, stack, "UV_FS_EVENT is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_FS_POLL(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_FS_POLL
  stack[0].ival = (int32_t)UV_FS_POLL;
  return 0;
#else
  env->die(env, stack, "UV_FS_POLL is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_IDLE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_IDLE
  stack[0].ival = (int32_t)UV_IDLE;
  return 0;
#else
  env->die(env, stack, "UV_IDLE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_NAMED_PIPE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_NAMED_PIPE
  stack[0].ival = (int32_t)UV_NAMED_PIPE;
  return 0;
#else
  env->die(env, stack, "UV_NAMED_PIPE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_POLL(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_POLL
  stack[0].ival = (int32_t)UV_POLL;
  return 0;
#else
  env->die(env, stack, "UV_POLL is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_PREPARE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_PREPARE
  stack[0].ival = (int32_t)UV_PREPARE;
  return 0;
#else
  env->die(env, stack, "UV_PREPARE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_PROCESS(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_PROCESS
  stack[0].ival = (int32_t)UV_PROCESS;
  return 0;
#else
  env->die(env, stack, "UV_PROCESS is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_STREAM(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_STREAM
  stack[0].ival = (int32_t)UV_STREAM;
  return 0;
#else
  env->die(env, stack, "UV_STREAM is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_TCP(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_TCP
  stack[0].ival = (int32_t)UV_TCP;
  return 0;
#else
  env->die(env, stack, "UV_TCP is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_TIMER(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_TIMER
  stack[0].ival = (int32_t)UV_TIMER;
  return 0;
#else
  env->die(env, stack, "UV_TIMER is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_TTY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_TTY
  stack[0].ival = (int32_t)UV_TTY;
  return 0;
#else
  env->die(env, stack, "UV_TTY is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_UDP(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_UDP
  stack[0].ival = (int32_t)UV_UDP;
  return 0;
#else
  env->die(env, stack, "UV_UDP is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_SIGNAL(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_SIGNAL
  stack[0].ival = (int32_t)UV_SIGNAL;
  return 0;
#else
  env->die(env, stack, "UV_SIGNAL is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_FILE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_FILE
  stack[0].ival = (int32_t)UV_FILE;
  return 0;
#else
  env->die(env, stack, "UV_FILE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_RUN_DEFAULT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_RUN_DEFAULT
  stack[0].ival = (int32_t)UV_RUN_DEFAULT;
  return 0;
#else
  env->die(env, stack, "UV_RUN_DEFAULT is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_RUN_ONCE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_RUN_ONCE
  stack[0].ival = (int32_t)UV_RUN_ONCE;
  return 0;
#else
  env->die(env, stack, "UV_RUN_ONCE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_RUN_NOWAIT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_RUN_NOWAIT
  stack[0].ival = (int32_t)UV_RUN_NOWAIT;
  return 0;
#else
  env->die(env, stack, "UV_RUN_NOWAIT is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_LOOP_BLOCK_SIGNAL(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_LOOP_BLOCK_SIGNAL
  stack[0].ival = (int32_t)UV_LOOP_BLOCK_SIGNAL;
  return 0;
#else
  env->die(env, stack, "UV_LOOP_BLOCK_SIGNAL is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_READABLE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_READABLE
  stack[0].ival = (int32_t)UV_READABLE;
  return 0;
#else
  env->die(env, stack, "UV_READABLE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_WRITABLE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_WRITABLE
  stack[0].ival = (int32_t)UV_WRITABLE;
  return 0;
#else
  env->die(env, stack, "UV_WRITABLE is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_DISCONNECT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_DISCONNECT
  stack[0].ival = (int32_t)UV_DISCONNECT;
  return 0;
#else
  env->die(env, stack, "UV_DISCONNECT is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_PRIORITIZED(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_PRIORITIZED
  stack[0].ival = (int32_t)UV_PRIORITIZED;
  return 0;
#else
  env->die(env, stack, "UV_PRIORITIZED is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_TTY_MODE_NORMAL(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_TTY_MODE_NORMAL
  stack[0].ival = (int32_t)UV_TTY_MODE_NORMAL;
  return 0;
#else
  env->die(env, stack, "UV_TTY_MODE_NORMAL is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_TTY_MODE_RAW(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_TTY_MODE_RAW
  stack[0].ival = (int32_t)UV_TTY_MODE_RAW;
  return 0;
#else
  env->die(env, stack, "UV_TTY_MODE_RAW is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_TTY_MODE_IO(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_TTY_MODE_IO
  stack[0].ival = (int32_t)UV_TTY_MODE_IO;
  return 0;
#else
  env->die(env, stack, "UV_TTY_MODE_IO is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_JOIN_GROUP(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_JOIN_GROUP
  stack[0].ival = (int32_t)UV_JOIN_GROUP;
  return 0;
#else
  env->die(env, stack, "UV_JOIN_GROUP is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

int32_t SPVM__Go__UV__Constant__UV_LEAVE_GROUP(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef UV_LEAVE_GROUP
  stack[0].ival = (int32_t)UV_LEAVE_GROUP;
  return 0;
#else
  env->die(env, stack, "UV_LEAVE_GROUP is not defined on the system", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#endif
}

