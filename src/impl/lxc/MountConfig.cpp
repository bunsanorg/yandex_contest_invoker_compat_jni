#include "com_yandex_contest_invoker_impl_lxc_MountConfig.h"

#include "yandex/contest/invoker/compat/jni/impl/lxc/MountConfig.hpp"

#include "yandex/contest/invoker/compat/jni/impl/unistd/MountEntry.hpp"

#include "yandex/contest/invoker/compat/jni/CXXClass.hpp"
#include "yandex/contest/invoker/compat/jni/FunctionHelper.hpp"
#include "yandex/contest/invoker/compat/jni/String.hpp"
#include "yandex/contest/invoker/compat/jni/Collection.hpp"

#include "yandex/contest/invoker/compat/jni/config/load.hpp"

using namespace yandex::contest::invoker::compat::jni;
namespace lxc = yandex::contest::system::lxc;

namespace
{
    CXXClass<lxc::MountConfig> mountConfigClass_;
}

void Java_com_yandex_contest_invoker_impl_lxc_MountConfig_classInit(JNIEnv *env, jclass mountConfigClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    mountConfigClass_.assign(mountConfigClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_lxc_MountConfig_finalize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, mountConfigClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace lxc{namespace mount_config
{
    LocalRef<jobject> create(const system::lxc::MountConfig &config)
    {
        return mountConfigClass_.setPointerCreate(config);
    }
}}}}}}}}

void Java_com_yandex_contest_invoker_impl_lxc_MountConfig_create(
    JNIEnv *env, jobject self, jobject mountConfig)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    mountConfigClass_.copyToPointer(self, config::load<lxc::MountConfig>(mountConfig));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jstring Java_com_yandex_contest_invoker_impl_lxc_MountConfig_fstab(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, mountConfigClass_, self)
    if (this_->fstab)
        return newStringUTF(this_->fstab.get().string()).release();
    else
        return nullptr;
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_lxc_MountConfig_entries(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, mountConfigClass_, self)
    if (this_->entries)
        return newArrayList(this_->entries.get(), impl::unistd::mount_entry::create).release();
    else
        return nullptr;
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
