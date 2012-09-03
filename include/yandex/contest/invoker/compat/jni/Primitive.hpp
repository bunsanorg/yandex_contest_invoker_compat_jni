#pragma once

#include "yandex/contest/invoker/compat/jni/Context.hpp"
#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"

#include "yandex/contest/invoker/compat/jni/traits/jinfo.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni
{
    template <typename T>
    LocalRef<jobject> newPrimitiveWrapper(const T obj)
    {
        typedef traits::jinfo<T> jinfo;
        static_assert(jinfo::is_primitive, "Should be primitive.");

        const Context::Handle ctx = Context::getContext();
        LocalRef<jclass> clazz(
            ctx->env()->FindClass(boost::mpl::c_str<typename jinfo::jwrapperclass>::value));
        jmethodID valueOfId = ctx->env()->GetStaticMethodID(
            clazz.get(), "valueOf", boost::mpl::c_str<typename jinfo::valueOfSig>::value);
        LocalRef<jobject> wrapper(ctx->env()->CallStaticObjectMethod(clazz.get(), valueOfId, obj));
        ctx->throwIfOccured();
        return wrapper;
    }
}}}}}
