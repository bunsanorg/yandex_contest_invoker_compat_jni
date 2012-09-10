#include "com_yandex_contest_invoker_impl_filesystem_FIFO.h"

#include "yandex/contest/invoker/compat/jni/impl/filesystem/FIFO.hpp"

#include "yandex/contest/invoker/compat/jni/CXXClass.hpp"
#include "yandex/contest/invoker/compat/jni/FunctionHelper.hpp"
#include "yandex/contest/invoker/compat/jni/String.hpp"

using namespace yandex::contest::invoker::compat::jni;
namespace filesystem = yandex::contest::invoker::filesystem;

namespace
{
    CXXClass<filesystem::FIFO> fifoClass_;
}

void Java_com_yandex_contest_invoker_impl_filesystem_FIFO_classInit(JNIEnv *env, jclass fifoClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    fifoClass_.assign(fifoClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace filesystem{namespace fifo
{
    LocalRef<jobject> create(const invoker::filesystem::FIFO &fifo)
    {
        return fifoClass_.setPointerCreate(fifo);
    }
}}}}}}}}
