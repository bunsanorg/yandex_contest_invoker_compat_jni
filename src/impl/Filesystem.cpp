#include "com_yandex_contest_invoker_impl_Filesystem.h"

#include <yandex/contest/invoker/compat/jni/impl/Filesystem.hpp>
#include <yandex/contest/invoker/compat/jni/impl/unistd/FileStatus.hpp>

#include <yandex/contest/invoker/compat/jni/config/load.hpp>
#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::Filesystem;
namespace unistd = yandex::contest::system::unistd;

namespace
{
    CxxClass<Filesystem> filesystemClass_;
}

void Java_com_yandex_contest_invoker_impl_Filesystem_classInit(
    JNIEnv *env, jclass filesystemClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    filesystemClass_.assign(filesystemClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace filesystem
{
    LocalRef<jobject> create(Filesystem &filesystem)
    {
        return filesystemClass_.setReferenceCreate(filesystem);
    }
}}}}}}}

jstring Java_com_yandex_contest_invoker_impl_Filesystem_containerRoot(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, filesystemClass_, self)
    return newStringUTF(this_->containerRoot().string()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jstring Java_com_yandex_contest_invoker_impl_Filesystem_keepInRoot(
    JNIEnv *env, jobject self, jstring path)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, filesystemClass_, self)
    return newStringUTF(this_->keepInRoot(getStringUTF(path)).string()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_Filesystem_push(
    JNIEnv *env, jobject self, jstring local, jstring remote, jobject ownerId, jint mode)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, filesystemClass_, self)
    this_->push(getStringUTF(local), getStringUTF(remote),
                config::load<unistd::access::Id>(ownerId), mode);
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_Filesystem_pushLink(
    JNIEnv *env, jobject self, jstring local, jstring remote, jobject ownerId, jint mode)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, filesystemClass_, self)
    this_->pushLink(getStringUTF(local), getStringUTF(remote),
                    config::load<unistd::access::Id>(ownerId), mode);
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_Filesystem_getFileStatus(
    JNIEnv *env, jobject self, jstring remote)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, filesystemClass_, self)
    return impl::unistd::file_status::create(
        this_->fileStatus(getStringUTF(remote))
    ).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_Filesystem_setOwnerId(
    JNIEnv *env, jobject self, jstring remote, jobject ownerId)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, filesystemClass_, self)
    this_->setOwnerId(
        getStringUTF(remote), config::load<unistd::access::Id>(ownerId)
    );
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_Filesystem_setMode(
    JNIEnv *env, jobject self, jstring remote, jint mode)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, filesystemClass_, self)
    this_->setMode(getStringUTF(remote), mode);
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_Filesystem_pull(
    JNIEnv *env, jobject self, jstring local, jstring remote)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, filesystemClass_, self)
    this_->pull(getStringUTF(local), getStringUTF(remote));
    YANDEX_JNI_METHOD_END_VOID(env)
}
