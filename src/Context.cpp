#include <yandex/contest/invoker/compat/jni/Context.hpp>
#include <yandex/contest/invoker/compat/jni/Error.hpp>
#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {

Context::Context(JavaVM *const jvm) : jvm_(jvm), detach_(true) {
  BOOST_ASSERT(jvm_);
  void *env = env_;
  jvm_->AttachCurrentThread(&env, nullptr);
  env_ = static_cast<JNIEnv *>(env);
  BOOST_ASSERT(env_);
}

Context::Context() : Context(getGlobalJVM()) {}

Context::Context(JNIEnv *const env) : env_(env), detach_(false) {
  BOOST_ASSERT(env_);
  jvm_ = getGlobalJVM();
  BOOST_ASSERT(jvm_);
}

Context::~Context() {
  if (detach_) jvm_->DetachCurrentThread();
}

JavaVM *Context::jvm() noexcept { return jvm_; }

JNIEnv *Context::env() {
  throwIfOccured();
  return env_;
}

JNIEnv *Context::envNoExcept() noexcept { return env_; }

void Context::throwIfOccured() {
  if (env_->ExceptionCheck()) BOOST_THROW_EXCEPTION(JavaError());
}

void Context::throwNew(const char *const className, const char *const message) {
  throwNewFromEnv(env(), className, message);
  throwIfOccured();
}

void Context::throwNewFromEnv(JNIEnv *env, const char *const className,
                              const char *const message) noexcept {
  LocalRef<jclass> clazz(env->FindClass(className));
  if (env->ExceptionCheck()) return;
  env->ThrowNew(clazz.get(), message);
  BOOST_ASSERT(env->ExceptionCheck());
}

}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
