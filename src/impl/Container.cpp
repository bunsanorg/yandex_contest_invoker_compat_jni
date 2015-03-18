#include "com_yandex_contest_invoker_impl_Container.h"

#include <yandex/contest/invoker/compat/jni/impl/Filesystem.hpp>
#include <yandex/contest/invoker/compat/jni/impl/process_group/DefaultSettings.hpp>
#include <yandex/contest/invoker/compat/jni/impl/ProcessGroup.hpp>

#include <yandex/contest/invoker/compat/jni/config/load.hpp>
#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/HandleHelper.hpp>

#include <yandex/contest/invoker/compat/ContainerContext.hpp>

#include <yandex/contest/StreamLog.hpp>
#include <yandex/contest/system/lxc/Config.hpp>

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::compat::ContainerContext;
using yandex::contest::invoker::compat::ContainerContextPointer;
using yandex::contest::invoker::ContainerConfig;
using yandex::contest::invoker::ProcessGroup;
namespace lxc = yandex::contest::system::lxc;

namespace
{
    CxxClass<ContainerContextPointer> containerClass_;
    jfieldID filesystemId_;
}

void Java_com_yandex_contest_invoker_impl_Container_classInit(JNIEnv *env, jclass containerClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    containerClass_.assign(containerClass, "impl");
    filesystemId_ = containerClass_.getFieldId("filesystem", "Lcom/yandex/contest/invoker/impl/Filesystem;");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_Container_finalize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, containerClass_, self)
    if (this_ && *this_)
        STREAM_ERROR << "Container was not destroyed.";
    containerClass_.finalize(self);
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_Container_destroy(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_HANDLE_DESTROY(env, containerClass_, self)
}

jboolean Java_com_yandex_contest_invoker_impl_Container_exists(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_HANDLE_EXISTS(env, containerClass_, self)
}

/// Signature: ()V
void Java_com_yandex_contest_invoker_impl_Container_create__(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    containerClass_.copyToPointer(self, ContainerContext::create());
    YANDEX_JNI_METHOD_END_VOID(env)
}

/// Signature: (Lcom/yandex/contest/invoker/IContainerConfig;)V
void Java_com_yandex_contest_invoker_impl_Container_create__Lcom_yandex_contest_invoker_IContainerConfig_2(
    JNIEnv *env, jobject self, jobject containerConfig)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    containerClass_.copyToPointer(
        self, ContainerContext::create(config::load<ContainerConfig>(containerConfig)));
    YANDEX_JNI_METHOD_END_VOID(env)
}

/// Signature: (Lcom/yandex/contest/invoker/lxc/ILxcConfig;)V
void Java_com_yandex_contest_invoker_impl_Container_create__Lcom_yandex_contest_invoker_lxc_ILxcConfig_2(
    JNIEnv *env, jobject self, jobject lxcConfig)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    containerClass_.copyToPointer(
        self, ContainerContext::create(config::load<lxc::Config>(lxcConfig)));
    YANDEX_JNI_METHOD_END_VOID(env)
}

/// Signature: (Lcom/yandex/contest/invoker/IContainerConfig;Lcom/yandex/contest/invoker/lxc/ILxcConfig;)V
void Java_com_yandex_contest_invoker_impl_Container_create__Lcom_yandex_contest_invoker_IContainerConfig_2Lcom_yandex_contest_invoker_lxc_ILxcConfig_2(
    JNIEnv *env, jobject self, jobject containerConfig, jobject lxcConfig)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    containerClass_.copyToPointer(
        self, ContainerContext::create(config::load<ContainerConfig>(containerConfig),
                                       config::load<lxc::Config>(lxcConfig)));
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_Container_createFilesystem(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_CONTEXT_THIS(env, ctx, containerClass_, self)
    LocalRef<jobject> filesystem(impl::filesystem::create((*this_)->member().filesystem()));
    ctx->env()->SetObjectField(self, filesystemId_, filesystem.get());
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_Container_createProcessGroup(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, containerClass_, self)
    return impl::process_group::create((*this_)->createProcessGroup()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_Container_getProcessGroupDefaultSettings(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, containerClass_, self)
    return impl::process_group::default_settings::create(
        (*this_)->member().processGroupDefaultSettings()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_Container_setProcessGroupDefaultSettings(
    JNIEnv *env, jobject self, jobject processGroupDefaultSettings)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, containerClass_, self)
    (*this_)->member().setProcessGroupDefaultSettings(
        config::load<ProcessGroup::DefaultSettings>(processGroupDefaultSettings));
    YANDEX_JNI_METHOD_END_VOID(env)
}
