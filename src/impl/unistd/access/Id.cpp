#include "com_yandex_contest_invoker_impl_unistd_access_Id.h"

#include <yandex/contest/invoker/compat/jni/impl/unistd/access/Id.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::system::unistd::access::Id;

namespace
{
    CxxClass<Id> idClass_;
}

void Java_com_yandex_contest_invoker_impl_unistd_access_Id_classInit(JNIEnv *env, jclass idClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    idClass_.assign(idClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_unistd_access_Id_finalize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, idClass_, self);
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace unistd{namespace access{namespace id
{
    LocalRef<jobject> create(const system::unistd::access::Id &id)
    {
        return idClass_.setPointerCreate(id);
    }
}}}}}}}}}

void Java_com_yandex_contest_invoker_impl_unistd_access_Id_create(
    JNIEnv *env, jobject self, jint uid, jint gid)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    idClass_.copyToPointer(self, Id(uid, gid));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jint Java_com_yandex_contest_invoker_impl_unistd_access_Id_getUid(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, idClass_, self)
    return this_->uid;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jint Java_com_yandex_contest_invoker_impl_unistd_access_Id_getGid(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, idClass_, self)
    return this_->gid;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}
