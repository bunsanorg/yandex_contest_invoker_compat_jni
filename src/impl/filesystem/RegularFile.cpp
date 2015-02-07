#include "com_yandex_contest_invoker_impl_filesystem_RegularFile.h"

#include <yandex/contest/invoker/compat/jni/impl/filesystem/RegularFile.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>

using namespace yandex::contest::invoker::compat::jni;
namespace filesystem = yandex::contest::invoker::filesystem;

namespace
{
    CxxClass<filesystem::RegularFile> regularFileClass_;
}

void Java_com_yandex_contest_invoker_impl_filesystem_RegularFile_classInit(
    JNIEnv *env, jclass regularFileClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    regularFileClass_.assign(regularFileClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace filesystem{namespace regular_file
{
    LocalRef<jobject> create(const invoker::filesystem::RegularFile &regularFile)
    {
        return regularFileClass_.setPointerCreate(regularFile);
    }
}}}}}}}}

jstring Java_com_yandex_contest_invoker_impl_filesystem_RegularFile_getSource(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, regularFileClass_, self)
    if (this_->source)
        return newStringUTF(this_->source->string()).release();
    else
        return nullptr;
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
