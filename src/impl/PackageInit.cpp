#include "com_yandex_contest_invoker_impl_PackageInit.h"
#include "com_yandex_contest_invoker_impl_PackageInitClasses.h"

#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>
#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

using namespace yandex::contest::invoker::compat::jni;

jobjectArray Java_com_yandex_contest_invoker_impl_PackageInit_getClasses(JNIEnv *env, jclass)
{
    Context::registerGlobalJVM(env);
    YANDEX_JNI_METHOD_BEGIN_CONTEXT(env, ctx)
    LocalRef<jclass> classClass(ctx->env()->FindClass("java/lang/Class"));
    LocalRef<jobjectArray> classes(ctx->env()->NewObjectArray(
        com_yandex_contest_invoker_impl_classNamesSize, classClass.get(), nullptr));
    for (std::size_t i = 0; i < com_yandex_contest_invoker_impl_classNamesSize; ++i)
    {
        const char *const className = com_yandex_contest_invoker_impl_classNames[i];
        LocalRef<jclass> packageClass(ctx->env()->FindClass(className));
        ctx->env()->SetObjectArrayElement(classes.get(), i, packageClass.get());
    }
    return classes.release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_PackageInit_deinit(JNIEnv *, jclass)
{
    Context::unregisterGlobalJVM();
}
