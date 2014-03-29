#include "com_yandex_contest_invoker_impl_process_group_ProcessGroupDefaultSettings.h"

#include "yandex/contest/invoker/compat/jni/impl/File.hpp"

#include "yandex/contest/invoker/compat/jni/impl/process_group/DefaultSettings.hpp"
#include "yandex/contest/invoker/compat/jni/impl/process_group/ResourceLimits.hpp"

#include "yandex/contest/invoker/compat/jni/impl/process/DefaultSettings.hpp"

#include "yandex/contest/invoker/compat/jni/CxxClass.hpp"
#include "yandex/contest/invoker/compat/jni/FunctionHelper.hpp"

#include "yandex/contest/invoker/compat/jni/config/load.hpp"

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::ProcessGroup;

namespace
{
    CxxClass<ProcessGroup::DefaultSettings> defaultSettingsClass_;
}

void Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupDefaultSettings_classInit(
    JNIEnv *env, jclass defaultSettingsClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    defaultSettingsClass_.assign(defaultSettingsClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupDefaultSettings_finalize(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, defaultSettingsClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace process_group{namespace default_settings
{
    LocalRef<jobject> create(const ProcessGroup::DefaultSettings &defaultSettings)
    {
        return defaultSettingsClass_.setPointerCreate(defaultSettings);
    }
}}}}}}}}

void Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupDefaultSettings_create(
    JNIEnv *env, jobject self, jobject defaultSettings)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    defaultSettingsClass_.copyToPointer(
        self, config::load<ProcessGroup::DefaultSettings>(defaultSettings));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupDefaultSettings_getResourceLimits(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, defaultSettingsClass_, self)
    return impl::process_group::resource_limits::create(this_->resourceLimits).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_process_1group_ProcessGroupDefaultSettings_getProcessDefaultSettings(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, defaultSettingsClass_, self)
    return impl::process::default_settings::create(this_->processDefaultSettings).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
