#include "com_yandex_contest_invoker_impl_lxc_RootfsConfig.h"

#include <yandex/contest/invoker/compat/jni/impl/lxc/RootfsConfig.hpp>

#include <yandex/contest/invoker/compat/jni/config/load.hpp>
#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>

using namespace yandex::contest::invoker::compat::jni;
namespace invoker = yandex::contest::invoker;

namespace {
CxxClass<invoker::lxc::RootfsConfig> rootfsConfigClass_;
}  // namespace

void Java_com_yandex_contest_invoker_impl_lxc_RootfsConfig_classInit(
    JNIEnv *env, jclass rootfsConfigClass) {
  YANDEX_JNI_METHOD_BEGIN(env)
  rootfsConfigClass_.assign(rootfsConfigClass, "impl");
  YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_lxc_RootfsConfig_finalize(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_FINALIZE(env, rootfsConfigClass_, self)
}

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace lxc {
namespace rootfs_config {
LocalRef<jobject> create(const invoker::lxc::RootfsConfig &config) {
  return rootfsConfigClass_.setPointerCreate(config);
}
}  // namespace rootfs_config
}  // namespace lxc
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex

void Java_com_yandex_contest_invoker_impl_lxc_RootfsConfig_create(
    JNIEnv *env, jobject self, jobject config) {
  YANDEX_JNI_METHOD_BEGIN(env)
  rootfsConfigClass_.copyToPointer(
      self, config::load<invoker::lxc::RootfsConfig>(config));
  YANDEX_JNI_METHOD_END_VOID(env)
}

jstring Java_com_yandex_contest_invoker_impl_lxc_RootfsConfig_fsname(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, rootfsConfigClass_, self)
  if (this_->fsname) {
    return newStringUTF(this_->fsname->string()).release();
  } else {
    return nullptr;
  }
  YANDEX_JNI_METHOD_END_OBJECT(env)
}

jstring Java_com_yandex_contest_invoker_impl_lxc_RootfsConfig_mount(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, rootfsConfigClass_, self)
  if (this_->mount) {
    return newStringUTF(this_->mount->string()).release();
  } else {
    return nullptr;
  }
  YANDEX_JNI_METHOD_END_OBJECT(env)
}
