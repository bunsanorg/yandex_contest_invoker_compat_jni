#pragma once

/*!
 * \file
 *
 * \brief Helper functions and defines for classes with handle field.
 */

#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>

#define YANDEX_JNI_METHOD_HANDLE_EXISTS(ENV, CLASS, SELF) \
  YANDEX_JNI_METHOD_BEGIN_THIS(ENV, CLASS, SELF)          \
  return this_ && *this_;                                 \
  YANDEX_JNI_METHOD_END_PRIMITIVE(ENV)

#define YANDEX_JNI_METHOD_HANDLE_DESTROY(ENV, CLASS, SELF) \
  YANDEX_JNI_METHOD_FINALIZE(ENV, CLASS, SELF)
