#pragma once

/*!
 * \file
 *
 * \brief Helper functions and defines for native methods implementation.
 */

#include "yandex/contest/invoker/compat/jni/Error.hpp"
#include "yandex/contest/invoker/compat/jni/Context.hpp"
#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"
#include "yandex/contest/invoker/compat/jni/CXXClass.hpp"
#include "yandex/contest/invoker/compat/jni/NotNull.hpp"

#include "yandex/contest/invoker/ContainerError.hpp"

#include <memory>

#define YANDEX_JNI_METHOD_PRIVATE_CONTEXT_NAME privateContextInstance_

#define YANDEX_JNI_METHOD_BEGIN_CONTEXT(ENV, CTX) \
    try \
    { \
        const ::yandex::contest::invoker::compat::jni::Context::Handle CTX = \
            ::yandex::contest::invoker::compat::jni::Context::getContext(ENV);

#define YANDEX_JNI_METHOD_BEGIN(ENV) \
    YANDEX_JNI_METHOD_BEGIN_CONTEXT(ENV, YANDEX_JNI_METHOD_PRIVATE_CONTEXT_NAME)

#define YANDEX_JNI_METHOD_BEGIN_CONTEXT_THIS(ENV, CTX, CLASS, SELF) \
    YANDEX_JNI_METHOD_BEGIN_CONTEXT(ENV, CTX) \
    YANDEX_JNI_NOT_NULL(SELF); \
    const auto this_ = CLASS.getPointer(SELF);

#define YANDEX_JNI_METHOD_BEGIN_THIS(ENV, CLASS, SELF) \
    YANDEX_JNI_METHOD_BEGIN_CONTEXT_THIS(ENV, YANDEX_JNI_METHOD_PRIVATE_CONTEXT_NAME, CLASS, SELF)

#define YANDEX_JNI_METHOD_MAP_ERROR(ENV, ERROR, EXCEPTION) \
    catch (ERROR &e) \
    { \
        ::yandex::contest::invoker::compat::jni::Context::throwNewFromEnv(ENV, EXCEPTION, e.what()); \
    }

#define YANDEX_JNI_METHOD_END_VOID(ENV) \
    } \
    catch (::yandex::contest::invoker::compat::jni::JavaError &e) \
    { /*does nothing, exception was already thrown*/ } \
    /*here we map local exception classes to Java*/ \
    YANDEX_JNI_METHOD_MAP_ERROR(ENV, ::yandex::contest::invoker::ContainerIllegalStateError, \
        "java/lang/IllegalStateException") \
    YANDEX_JNI_METHOD_MAP_ERROR(ENV, std::exception, "com/yandex/contest/invoker/InvokerException")

#define YANDEX_JNI_METHOD_END_RETURN(ENV, RETURN) \
    YANDEX_JNI_METHOD_END_VOID(ENV) \
    return RETURN;

#define YANDEX_JNI_METHOD_END_OBJECT(ENV) \
    YANDEX_JNI_METHOD_END_RETURN(ENV, nullptr)

#define YANDEX_JNI_METHOD_END_PRIMITIVE(ENV) \
    YANDEX_JNI_METHOD_END_RETURN(ENV, 0)

#define YANDEX_JNI_METHOD_FINALIZE(ENV, CLASS, SELF) \
    YANDEX_JNI_METHOD_BEGIN(ENV) \
    CLASS.finalize(SELF); \
    YANDEX_JNI_METHOD_END_VOID(ENV)
