#include "com_yandex_contest_invoker_impl_unistd_FileStatus.h"

#include <yandex/contest/invoker/compat/jni/impl/unistd/FileStatus.hpp>

#include <yandex/contest/invoker/compat/jni/impl/unistd/access/Id.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>

using namespace yandex::contest::invoker::compat::jni;
namespace unistd = yandex::contest::system::unistd;

namespace
{
    CxxClass<unistd::FileStatus> fileStatusClass_;
}

void Java_com_yandex_contest_invoker_impl_unistd_FileStatus_classInit(
    JNIEnv *env, jclass fileStatusClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    fileStatusClass_.assign(fileStatusClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_unistd_FileStatus_finalize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, fileStatusClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace unistd{namespace file_status
{
    LocalRef<jobject> create(const system::unistd::FileStatus &fileStatus)
    {
        return fileStatusClass_.setPointerCreate(fileStatus);
    }
}}}}}}}}

jlong Java_com_yandex_contest_invoker_impl_unistd_FileStatus_ino(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->ino;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jint Java_com_yandex_contest_invoker_impl_unistd_FileStatus_mode(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->mode;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_unistd_FileStatus_nlink(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->nlink;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jobject Java_com_yandex_contest_invoker_impl_unistd_FileStatus_ownerId(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return impl::unistd::access::id::create(this_->ownerId).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jlong Java_com_yandex_contest_invoker_impl_unistd_FileStatus_size(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->size;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_unistd_FileStatus_blksize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->blksize;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_unistd_FileStatus_blocks(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->blocks;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_unistd_FileStatus_atime(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->atime;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_unistd_FileStatus_mtime(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->mtime;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jlong Java_com_yandex_contest_invoker_impl_unistd_FileStatus_ctime(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->ctime;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jint Java_com_yandex_contest_invoker_impl_unistd_FileStatus_getAccmode(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->accmode();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jint Java_com_yandex_contest_invoker_impl_unistd_FileStatus_getType(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->type();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jboolean Java_com_yandex_contest_invoker_impl_unistd_FileStatus_isFifo(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->isFifo();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jboolean Java_com_yandex_contest_invoker_impl_unistd_FileStatus_isCharDevice(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->isCharDevice();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jboolean Java_com_yandex_contest_invoker_impl_unistd_FileStatus_isDirectory(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->isDirectory();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jboolean Java_com_yandex_contest_invoker_impl_unistd_FileStatus_isBlockDevice(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->isBlockDevice();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jboolean Java_com_yandex_contest_invoker_impl_unistd_FileStatus_isRegularFile(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->isRegularFile();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jboolean Java_com_yandex_contest_invoker_impl_unistd_FileStatus_isSymbolicLink(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->isSymbolicLink();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jboolean Java_com_yandex_contest_invoker_impl_unistd_FileStatus_isSocket(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->isSocket();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jint Java_com_yandex_contest_invoker_impl_unistd_FileStatus_getPermissions(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileStatusClass_, self)
    return this_->permissions();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}
