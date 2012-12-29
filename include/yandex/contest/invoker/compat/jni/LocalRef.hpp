#pragma once

#include "yandex/contest/invoker/compat/jni/Context.hpp"

#include "bunsan/forward_constructor.hpp"

#include <memory>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni
{
    namespace local_ref_detail
    {
        struct DeleteLocalRef
        {
            void operator()(jobject obj) const noexcept
            {
                Context::getContext()->envNoExcept()->DeleteLocalRef(obj);
            }
        };
    }

    template <typename Ptr>
    class LocalRef;

    template <typename T>
    class LocalRef<T *>: public std::unique_ptr<T, local_ref_detail::DeleteLocalRef>
    {
    private:
        typedef std::unique_ptr<T, local_ref_detail::DeleteLocalRef> Base;

    public:
        BUNSAN_INHERIT_EXPLICIT_CONSTRUCTOR(LocalRef, Base)
    };
}}}}}
