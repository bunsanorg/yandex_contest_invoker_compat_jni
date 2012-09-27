#include "yandex/contest/invoker/compat/jni/Collection.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni
{
    void getIterable(jobject jobj, const std::function<void (jobject)> &cb)
    {
        const Context::Handle ctx = Context::getContext();
        LocalRef<jclass> clazz(ctx->env()->GetObjectClass(jobj));
        jmethodID iteratorId = ctx->env()->GetMethodID(clazz.get(), "iterator", "()Ljava/util/Iterator;");
        LocalRef<jobject> iter(ctx->env()->CallObjectMethod(jobj, iteratorId));
        LocalRef<jclass> iterClass(ctx->env()->GetObjectClass(iter.get()));
        jmethodID hasNextId = ctx->env()->GetMethodID(iterClass.get(), "hasNext", "()Z");
        jmethodID nextId = ctx->env()->GetMethodID(iterClass.get(), "next", "()Ljava/lang/Object;");
        while (ctx->env()->CallBooleanMethod(iter.get(), hasNextId))
        {
            LocalRef<jobject> jobj(ctx->env()->CallObjectMethod(iter.get(), nextId));
            ctx->throwIfOccured();
            cb(jobj.get());
        }
    }
}}}}}
