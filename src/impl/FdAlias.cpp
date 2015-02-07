#include "com_yandex_contest_invoker_impl_FdAlias.h"

#include <yandex/contest/invoker/compat/jni/impl/File.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/Enum.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::FdAlias;
using yandex::contest::invoker::AccessMode;

namespace
{
    CxxClass<FdAlias> fdAliasClass_;
}

void Java_com_yandex_contest_invoker_impl_FdAlias_classInit(
    JNIEnv *env, jclass fdAliasClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    fdAliasClass_.assign(fdAliasClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_FdAlias_finalize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, fdAliasClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace fd_alias
{
    LocalRef<jobject> create(const FdAlias &fdAlias)
    {
        return fdAliasClass_.setPointerCreate(fdAlias);
    }
}}}}}}}

jint Java_com_yandex_contest_invoker_impl_FdAlias_getFd(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fdAliasClass_, self)
    return this_->fd;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}
