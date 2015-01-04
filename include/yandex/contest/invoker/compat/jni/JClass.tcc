#pragma once

#include <boost/assert.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni
{
    template <typename ClassRef>
    void BasicJClass<ClassRef>::assign(jclass clazz)
    {
        class_.reset(clazz);
    }

    template <typename ClassRef>
    void BasicJClass<ClassRef>::assign(const char *const className)
    {
        const Context::Handle ctx = Context::getContext();
        LocalRef<jclass> clazz(ctx->env()->FindClass(className));
        ctx->throwIfOccured();
        assign(clazz.get());
    }

    template <typename ClassRef>
    jmethodID BasicJClass<ClassRef>::getMethodId(
        const char *const name, const char *const sig)
    {
        const Context::Handle ctx = Context::getContext();
        const jmethodID mId = ctx->env()->GetMethodID(clazz(), name, sig);
        ctx->throwIfOccured();
        return mId;
    }

    template <typename ClassRef>
    jmethodID BasicJClass<ClassRef>::getStaticMethodId(
        const char *const name, const char *const sig)
    {
        const Context::Handle ctx = Context::getContext();
        const jmethodID mId = ctx->env()->GetStaticMethodID(clazz(), name, sig);
        ctx->throwIfOccured();
        return mId;
    }

    template <typename ClassRef>
    jfieldID BasicJClass<ClassRef>::getFieldId(
        const char *const name, const char *const sig)
    {
        const Context::Handle ctx = Context::getContext();
        const jfieldID fId = ctx->env()->GetFieldID(clazz(), name, sig);
        ctx->throwIfOccured();
        return fId;
    }

    template <typename ClassRef>
    jfieldID BasicJClass<ClassRef>::getStaticFieldId(
        const char *const name, const char *const sig)
    {
        const Context::Handle ctx = Context::getContext();
        const jfieldID fId = ctx->env()->GetStaticFieldID(clazz(), name, sig);
        ctx->throwIfOccured();
        return fId;
    }

    template <typename ClassRef>
    jclass BasicJClass<ClassRef>::clazz() const
    {
        BOOST_ASSERT(class_);
        return class_.get();
    }
}}}}}
