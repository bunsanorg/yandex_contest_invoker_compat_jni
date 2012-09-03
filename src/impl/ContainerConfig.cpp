#include "common_invocation_impl_ContainerConfig.h"

#include "yandex/contest/invoker/compat/jni/impl/ContainerConfig.hpp"

#include "yandex/contest/invoker/compat/jni/impl/filesystem/Config.hpp"

#include "yandex/contest/invoker/compat/jni/impl/lxc/Config.hpp"

#include "yandex/contest/invoker/compat/jni/impl/process_group/DefaultSettings.hpp"

#include "yandex/contest/invoker/compat/jni/impl/ControlProcessConfig.hpp"

#include "yandex/contest/invoker/compat/jni/CXXClass.hpp"
#include "yandex/contest/invoker/compat/jni/FunctionHelper.hpp"
#include "yandex/contest/invoker/compat/jni/String.hpp"

#include "yandex/contest/invoker/compat/jni/config/load.hpp"

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::ContainerConfig;

namespace
{
    CXXClass<ContainerConfig> containerConfigClass_;
}

void Java_com_yandex_contest_invoker_impl_ContainerConfig_classInit(
    JNIEnv *env, jclass containerConfigClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    containerConfigClass_.assign(containerConfigClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_ContainerConfig_finalize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, containerConfigClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace container_config
{
    LocalRef<jobject> create(const ContainerConfig &config)
    {
        return containerConfigClass_.setPointerCreate(config);
    }
}}}}}}}

void Java_com_yandex_contest_invoker_impl_ContainerConfig_create(
    JNIEnv *env, jobject self, jobject containerConfig)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    containerConfigClass_.copyToPointer(self, config::load<ContainerConfig>(containerConfig));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jstring Java_com_yandex_contest_invoker_impl_ContainerConfig_getContainersDir(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, containerConfigClass_, self)
    return newStringUTF(this_->containersDir.string()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_ContainerConfig_getLXCConfig(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, containerConfigClass_, self)
    return impl::lxc::config::create(this_->lxcConfig).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_ContainerConfig_getProcessGroupDefaultSettings(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, containerConfigClass_, self)
    return impl::process_group::default_settings::create(this_->processGroupDefaultSettings).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_ContainerConfig_getControlProcessConfig(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, containerConfigClass_, self)
    return impl::control_process_config::create(this_->controlProcessConfig).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_ContainerConfig_getFilesystemConfig(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, containerConfigClass_, self)
    return impl::filesystem::config::create(this_->filesystemConfig).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_ContainerConfig_fromEnvironment(JNIEnv *env, jclass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    return impl::container_config::create(ContainerConfig::fromEnvironment()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
