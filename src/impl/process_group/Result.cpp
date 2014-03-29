#include "com_yandex_contest_invoker_impl_process_group_ProcessGroupResult.h"

#include "yandex/contest/invoker/compat/jni/impl/process_group/Result.hpp"
#include "yandex/contest/invoker/compat/jni/impl/process_group/ResourceUsage.hpp"

#include "yandex/contest/invoker/compat/jni/CxxClass.hpp"
#include "yandex/contest/invoker/compat/jni/FunctionHelper.hpp"
#include "yandex/contest/invoker/compat/jni/Enum.hpp"

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::ProcessGroup;

namespace
{
    CxxClass<ProcessGroup::Result> processGroupResultClass_;
    GlobalEnumClass<ProcessGroup::Result::CompletionStatus> completionStatusClass_;
}

void Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupResult_classInit(
    JNIEnv *env, jclass processGroupResultClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    processGroupResultClass_.assign(processGroupResultClass, "impl");
    completionStatusClass_.assign(
        "com/yandex/contest/invoker/process_group/IProcessGroupResult$CompletionStatus");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupResult_finalize(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, processGroupResultClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace process_group{namespace result
{
    LocalRef<jobject> create(const ProcessGroup::Result &result)
    {
        return processGroupResultClass_.setPointerCreate(result);
    }
}}}}}}}}

jobject Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupResult_getCompletionStatus(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupResultClass_, self)
    return completionStatusClass_.newEnum(this_->completionStatus).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupResult_getResourceUsage(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupResultClass_, self)
    return impl::process_group::resource_usage::create(this_->resourceUsage).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
