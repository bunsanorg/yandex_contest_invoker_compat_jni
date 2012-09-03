#pragma once

#include <jni.h>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace detail
{
    void requireNotNull(jobject jobj, const char *const function, const long line);

    /// \note Sometimes it may be more convenient to wrap jobject argument.
    template <typename T>
    inline T requireNotNullReturn(T jobj, const char *const function, const long line)
    {
        requireNotNull(jobj, function, line);
        return jobj;
    }
}}}}}}

#define YANDEX_JNI_NOT_NULL(JOBJ) \
    ::yandex::contest::invoker::compat::jni::detail::requireNotNullReturn( \
        JOBJ, BOOST_CURRENT_FUNCTION, __LINE__)
