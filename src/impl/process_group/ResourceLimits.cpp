#include "com_yandex_contest_invoker_impl_process_group_ProcessGroupResourceLimits.h"

#include <yandex/contest/invoker/compat/jni/impl/process_group/ResourceLimits.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>

#include <yandex/contest/invoker/compat/jni/config/load.hpp>

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::ProcessGroup;

namespace
{
    CxxClass<ProcessGroup::ResourceLimits> resourceLimitsClass_;
}

void Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupResourceLimits_classInit(
    JNIEnv *env, jclass resourceLimitsClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    resourceLimitsClass_.assign(resourceLimitsClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupResourceLimits_finalize(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, resourceLimitsClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace process_group{namespace resource_limits
{
    LocalRef<jobject> create(const ProcessGroup::ResourceLimits &resourceLimits)
    {
        return resourceLimitsClass_.setPointerCreate(resourceLimits);
    }
}}}}}}}}

void Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupResourceLimits_create(
    JNIEnv *env, jobject self, jobject resourceLimits)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    resourceLimitsClass_.copyToPointer(
        self, config::load<ProcessGroup::ResourceLimits>(resourceLimits));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jlong Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupResourceLimits_getRealTimeLimitMillis(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, resourceLimitsClass_, self)
    return std::chrono::duration_cast<std::chrono::milliseconds>(this_->realTimeLimit).count();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}
