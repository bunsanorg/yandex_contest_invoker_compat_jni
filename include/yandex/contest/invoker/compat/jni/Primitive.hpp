#pragma once

#include <yandex/contest/invoker/compat/jni/Context.hpp>
#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>
#include <yandex/contest/invoker/compat/jni/traits/jinfo.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {

template <typename T>
LocalRef<jobject> newPrimitiveWrapper(const T obj) {
  using jinfo = traits::jinfo<T>;
  static_assert(jinfo::is_primitive, "Should be primitive.");

  const Context::Handle ctx = Context::getContext();
  LocalRef<jclass> clazz(ctx->env()->FindClass(jinfo::jwrapperclass().c_str()));
  const jmethodID valueOfId = ctx->env()->GetStaticMethodID(
      clazz.get(), "valueOf", jinfo::valueOfSig().c_str());
  LocalRef<jobject> wrapper(
      ctx->env()->CallStaticObjectMethod(clazz.get(), valueOfId, obj));
  ctx->throwIfOccured();
  return wrapper;
}

}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
