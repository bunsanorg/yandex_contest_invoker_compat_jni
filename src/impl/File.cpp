#include "common_invocation_impl_File.h"

#include "yandex/contest/invoker/compat/jni/impl/File.hpp"

#include "yandex/contest/invoker/compat/jni/CXXClass.hpp"
#include "yandex/contest/invoker/compat/jni/FunctionHelper.hpp"
#include "yandex/contest/invoker/compat/jni/Enum.hpp"

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::File;
using yandex::contest::invoker::AccessMode;

namespace
{
    CXXClass<File> fileClass_;
    GlobalEnumClass<AccessMode> accessModeClass_;
}

void Java_com_yandex_contest_invoker_impl_File_classInit(JNIEnv *env, jclass fileClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    fileClass_.assign(fileClass, "impl");
    accessModeClass_.assign("com/yandex/contest/invoker/IStream$AccessMode");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_File_finalize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, fileClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace file
{
    LocalRef<jobject> create(const File &file)
    {
        return fileClass_.setPointerCreate(file);
    }
}}}}}}}

jstring Java_com_yandex_contest_invoker_impl_File_getPath(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileClass_, self)
    return newStringUTF(this_->path.string()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_File_getAccessMode(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, fileClass_, self)
    return accessModeClass_.newEnum(this_->accessMode).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
