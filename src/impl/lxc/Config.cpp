#include "com_yandex_contest_invoker_impl_lxc_LxcConfig.h"

#include <yandex/contest/invoker/compat/jni/impl/lxc/Config.hpp>
#include <yandex/contest/invoker/compat/jni/impl/lxc/MountConfig.hpp>
#include <yandex/contest/invoker/compat/jni/impl/lxc/RootfsConfig.hpp>

#include <yandex/contest/invoker/compat/jni/Collection.hpp>
#include <yandex/contest/invoker/compat/jni/config/load.hpp>
#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/Enum.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>
#include <yandex/contest/invoker/compat/jni/Primitive.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>

using namespace yandex::contest::invoker::compat::jni;
namespace invoker = yandex::contest::invoker;

namespace {
CxxClass<invoker::lxc::Config> configClass_;
GlobalEnumClass<invoker::lxc::Config::Arch> archEnumClass_;
}  // namespace

void Java_com_yandex_contest_invoker_impl_lxc_LxcConfig_classInit(
    JNIEnv *env, jclass configClass) {
  YANDEX_JNI_METHOD_BEGIN(env)
  configClass_.assign(configClass, "impl");
  archEnumClass_.assign("com/yandex/contest/invoker/lxc/ILxcConfig$Arch");
  YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_lxc_LxcConfig_finalize(JNIEnv *env,
                                                                 jobject self) {
  YANDEX_JNI_METHOD_FINALIZE(env, configClass_, self)
}

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace lxc {
namespace config {
LocalRef<jobject> create(const invoker::lxc::Config &config) {
  return configClass_.setPointerCreate(config);
}
}  // namespace config
}  // namespace lxc
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex

void Java_com_yandex_contest_invoker_impl_lxc_LxcConfig_create(JNIEnv *env,
                                                               jobject self,
                                                               jobject config) {
  YANDEX_JNI_METHOD_BEGIN(env)
  configClass_.copyToPointer(self, config::load<invoker::lxc::Config>(config));
  YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_lxc_LxcConfig_arch(JNIEnv *env,
                                                                jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
  if (this_->arch) {
    return archEnumClass_.newEnum(this_->arch.get()).release();
  } else {
    return nullptr;
  }
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jstring Java_com_yandex_contest_invoker_impl_lxc_LxcConfig_utsname(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
  if (this_->utsname) {
    return newStringUTF(this_->utsname.get()).release();
  } else {
    return nullptr;
  }
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jstring Java_com_yandex_contest_invoker_impl_lxc_LxcConfig_console(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
  if (this_->console) {
    return newStringUTF(this_->console->string()).release();
  } else {
    return nullptr;
  }
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_lxc_LxcConfig_tty(JNIEnv *env,
                                                               jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
  if (this_->tty) {
    return newPrimitiveWrapper<jint>(this_->tty.get()).release();
  } else {
    return nullptr;
  }
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jstring Java_com_yandex_contest_invoker_impl_lxc_LxcConfig_devttydir(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
  if (this_->devttydir) {
    return newStringUTF(this_->devttydir->string()).release();
  } else {
    return nullptr;
  }
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_lxc_LxcConfig_mount(JNIEnv *env,
                                                                 jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
  if (this_->mount) {
    return impl::lxc::mount_config::create(this_->mount.get()).release();
  } else {
    return nullptr;
  }
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_lxc_LxcConfig_rootfs(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
  if (this_->rootfs) {
    return impl::lxc::rootfs_config::create(this_->rootfs.get()).release();
  } else {
    return nullptr;
  }
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jstring Java_com_yandex_contest_invoker_impl_lxc_LxcConfig_pivotdir(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
  if (this_->pivotdir) {
    return newStringUTF(this_->pivotdir->string()).release();
  } else {
    return nullptr;
  }
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_lxc_LxcConfig_cgroup(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
  if (this_->cgroup) {
    return newHashMap(this_->cgroup.get(), newStringUTF, newStringUTF)
        .release();
  } else {
    return nullptr;
  }
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_lxc_LxcConfig_cap_1drop(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, configClass_, self)
  if (this_->cap_drop) {
    return newHashSet(this_->cap_drop.get(), newStringUTF).release();
  } else {
    return nullptr;
  }
  YANDEX_JNI_METHOD_END_OBJECT(env)
}
