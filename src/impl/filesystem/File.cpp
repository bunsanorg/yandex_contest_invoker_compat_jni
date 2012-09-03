#include "common_invocation_impl_filesystem_File.h"

#include "yandex/contest/invoker/filesystem/File.hpp"

#include "yandex/contest/invoker/compat/jni/impl/unistd/access/Id.hpp"

#include "yandex/contest/invoker/compat/jni/CXXClass.hpp"
#include "yandex/contest/invoker/compat/jni/FunctionHelper.hpp"
#include "yandex/contest/invoker/compat/jni/String.hpp"

using namespace yandex::contest::invoker::compat::jni;
namespace filesystem = yandex::contest::invoker::filesystem;

namespace
{
    CXXClass<filesystem::File> fileClass_;
}

void Java_com_yandex_contest_invoker_impl_filesystem_File_classInit(JNIEnv *env, jclass fileClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    fileClass_.assign(fileClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_filesystem_File_finalize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, fileClass_, self)
}

jstring Java_com_yandex_contest_invoker_impl_filesystem_File_getPath(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileClass_, self)
    return newStringUTF(this_->path.string()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jint Java_com_yandex_contest_invoker_impl_filesystem_File_getMode(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileClass_, self)
    return this_->mode;
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jobject Java_com_yandex_contest_invoker_impl_filesystem_File_getOwnerId(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileClass_, self)
    return impl::unistd::access::id::create(this_->ownerId).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
