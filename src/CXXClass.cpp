#include "yandex/contest/invoker/compat/jni/CXXClass.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni
{
    void BasicCXXClass::assignCXX(const char *const ptrName)
    {
        const Context::Handle ctx = Context::getContext();
        defCtorId_ = ctx->env()->GetMethodID(clazz(), "<init>", "()V");
        ptrId_ = ctx->env()->GetFieldID(clazz(), ptrName, "J");
    }
}}}}}
