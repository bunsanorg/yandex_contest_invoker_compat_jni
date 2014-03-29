#include "com_yandex_contest_invoker_impl_Pipe.h"

#include "yandex/contest/invoker/compat/jni/impl/Pipe.hpp"
#include "yandex/contest/invoker/compat/jni/impl/Stream.hpp"

#include "yandex/contest/invoker/compat/jni/CxxClass.hpp"
#include "yandex/contest/invoker/compat/jni/FunctionHelper.hpp"

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::Stream;
using yandex::contest::invoker::Pipe;

namespace
{
    CxxClass<Pipe> pipeClass_;
}

void Java_com_yandex_contest_invoker_impl_Pipe_classInit(JNIEnv *env, jclass pipeClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    pipeClass_.assign(pipeClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_Pipe_finalize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, pipeClass_, self);
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace pipe
{
    LocalRef<jobject> create(const Pipe &pipe)
    {
        return pipeClass_.setPointerCreate(pipe);
    }
}}}}}}}

jobject Java_com_yandex_contest_invoker_impl_Pipe_getInputStream(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, pipeClass_, self)
    return impl::stream::create(this_->readEnd()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_Pipe_getOutputStream(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, pipeClass_, self)
    return impl::stream::create(this_->writeEnd()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
