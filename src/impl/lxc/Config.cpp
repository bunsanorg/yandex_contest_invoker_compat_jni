#include "com_yandex_contest_invoker_impl_lxc_LXCConfig.h"

#include "yandex/contest/invoker/compat/jni/impl/lxc/Config.hpp"
#include "yandex/contest/invoker/compat/jni/impl/lxc/MountConfig.hpp"

#include "yandex/contest/invoker/compat/jni/CXXClass.hpp"
#include "yandex/contest/invoker/compat/jni/FunctionHelper.hpp"
#include "yandex/contest/invoker/compat/jni/Collection.hpp"
#include "yandex/contest/invoker/compat/jni/String.hpp"
#include "yandex/contest/invoker/compat/jni/Primitive.hpp"
#include "yandex/contest/invoker/compat/jni/Enum.hpp"

#include "yandex/contest/invoker/compat/jni/config/load.hpp"

using namespace yandex::contest::invoker::compat::jni;
namespace lxc = yandex::contest::system::lxc;

namespace
{
    CXXClass<lxc::Config> configClass_;
    GlobalEnumClass<lxc::Config::Arch> archEnumClass_;
}

void Java_com_yandex_contest_invoker_impl_lxc_LXCConfig_classInit(
    JNIEnv *env, jclass configClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    configClass_.assign(configClass, "impl");
    archEnumClass_.assign("com/yandex/contest/invoker/lxc/ILXCConfig$Arch");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_lxc_LXCConfig_finalize(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, configClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace lxc{namespace config
{
    LocalRef<jobject> create(const system::lxc::Config &config)
    {
        return configClass_.setPointerCreate(config);
    }
}}}}}}}}

void Java_com_yandex_contest_invoker_impl_lxc_LXCConfig_create(
    JNIEnv *env, jobject self, jobject filesystemConfig)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    configClass_.copyToPointer(self, config::load<lxc::Config>(filesystemConfig));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_lxc_LXCConfig_arch(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
    if (this_->arch)
        return archEnumClass_.newEnum(this_->arch.get()).release();
    else
        return nullptr;
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jstring Java_com_yandex_contest_invoker_impl_lxc_LXCConfig_utsname(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
    if (this_->utsname)
        return newStringUTF(this_->utsname.get()).release();
    else
        return nullptr;
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jstring Java_com_yandex_contest_invoker_impl_lxc_LXCConfig_console(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
    if (this_->console)
        return newStringUTF(this_->console.get().string()).release();
    else
        return nullptr;
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_lxc_LXCConfig_tty(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
    if (this_->tty)
        return newPrimitiveWrapper<jint>(this_->tty.get()).release();
    else
        return nullptr;
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_lxc_LXCConfig_mount(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
    if (this_->mount)
        return impl::lxc::mount_config::create(this_->mount.get()).release();
    else
        return nullptr;
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_lxc_LXCConfig_cgroup(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
    if (this_->cgroup)
        return newHashMap(this_->cgroup.get(), newStringUTF, newStringUTF).release();
    else
        return nullptr;
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_lxc_LXCConfig_cap_1drop(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
    if (this_->cap_drop)
        return newHashSet(this_->cap_drop.get(), newStringUTF).release();
    else
        return nullptr;
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
