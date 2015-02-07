#include "com_yandex_contest_invoker_impl_process_ProcessResult.h"

#include <yandex/contest/invoker/compat/jni/impl/process/ResourceUsage.hpp>
#include <yandex/contest/invoker/compat/jni/impl/process/Result.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/Enum.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::Process;

namespace
{
    CxxClass<Process::Result> processResultClass_;
    GlobalEnumClass<Process::Result::CompletionStatus> completionStatusClass_;
    GlobalJClass integerClass_;
    jmethodID integerCtorId_;
    GlobalEnumClass<jclass> signalClass_;
}

void Java_com_yandex_contest_invoker_impl_process_ProcessResult_classInit(
    JNIEnv *env, jclass processResultClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    processResultClass_.assign(processResultClass, "impl");
    completionStatusClass_.assign(
        "com/yandex/contest/invoker/process/IProcessResult$CompletionStatus");
    integerClass_.assign("java/lang/Integer");
    integerCtorId_ = integerClass_.getMethodId("<init>", "(I)V");
    signalClass_.assign("com/yandex/contest/invoker/Signal");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_process_ProcessResult_finalize(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, processResultClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace process{namespace result
{
    LocalRef<jobject> create(const Process::Result &result)
    {
        return processResultClass_.setPointerCreate(result);
    }
}}}}}}}}

jobject Java_com_yandex_contest_invoker_impl_process_ProcessResult_getCompletionStatus(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processResultClass_, self)
    return completionStatusClass_.newEnum(this_->completionStatus).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_process_ProcessResult_getExitStatus(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processResultClass_, self)
    if (this_->exitStatus)
    {
        LocalRef<jobject> ret(integerClass_.newObject(
            integerCtorId_, static_cast<jint>(this_->exitStatus.get())));
        return ret.release();
    }
    else
    {
        return nullptr;
    }
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_process_ProcessResult_getTermSig(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processResultClass_, self)
    if (this_->termSig)
        return signalClass_.newEnumByOrdinal(this_->termSig.get() - 1).release();
    else
        return nullptr;
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_process_ProcessResult_getResourceUsage(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processResultClass_, self)
    return impl::process::resource_usage::create(this_->resourceUsage).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
