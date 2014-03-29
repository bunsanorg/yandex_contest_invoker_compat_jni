#include "com_yandex_contest_invoker_impl_filesystem_Fifo.h"

#include <yandex/contest/invoker/compat/jni/impl/filesystem/Fifo.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>

using namespace yandex::contest::invoker::compat::jni;
namespace filesystem = yandex::contest::invoker::filesystem;

namespace
{
    CxxClass<filesystem::Fifo> fifoClass_;
}

void Java_com_yandex_contest_invoker_impl_filesystem_Fifo_classInit(JNIEnv *env, jclass fifoClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    fifoClass_.assign(fifoClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace filesystem{namespace fifo
{
    LocalRef<jobject> create(const invoker::filesystem::Fifo &fifo)
    {
        return fifoClass_.setPointerCreate(fifo);
    }
}}}}}}}}
