#include <yandex/contest/invoker/compat/jni/Collection.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {

void getIterable(jobject jobj, const std::function<void(jobject)> &cb) {
  const Context::Handle ctx = Context::getContext();
  LocalRef<jclass> clazz(ctx->env()->GetObjectClass(jobj));
  const jmethodID iteratorId = ctx->env()->GetMethodID(
      clazz.get(), "iterator", "()Ljava/util/Iterator;");
  LocalRef<jobject> iter(ctx->env()->CallObjectMethod(jobj, iteratorId));
  LocalRef<jclass> iterClass(ctx->env()->GetObjectClass(iter.get()));
  const jmethodID hasNextId =
      ctx->env()->GetMethodID(iterClass.get(), "hasNext", "()Z");
  const jmethodID nextId =
      ctx->env()->GetMethodID(iterClass.get(), "next", "()Ljava/lang/Object;");
  while (ctx->env()->CallBooleanMethod(iter.get(), hasNextId)) {
    LocalRef<jobject> jobj(ctx->env()->CallObjectMethod(iter.get(), nextId));
    ctx->throwIfOccured();
    cb(jobj.get());
  }
}

void getMap(jobject jobj, const std::function<void(jobject, jobject)> &cb) {
  const Context::Handle ctx = Context::getContext();
  LocalRef<jclass> clazz(ctx->env()->GetObjectClass(jobj));
  const jmethodID entrySetId =
      ctx->env()->GetMethodID(clazz.get(), "entrySet", "()Ljava/util/Set;");
  LocalRef<jobject> entrySet(ctx->env()->CallObjectMethod(jobj, entrySetId));
  LocalRef<jclass> mapEntryClass(ctx->env()->FindClass("java/util/Map$Entry"));
  const jmethodID getKeyId = ctx->env()->GetMethodID(
      mapEntryClass.get(), "getKey", "()Ljava/lang/Object;");
  const jmethodID getValueId = ctx->env()->GetMethodID(
      mapEntryClass.get(), "getValue", "()Ljava/lang/Object;");
  ctx->throwIfOccured();
  getIterable(entrySet.get(), [&ctx, &cb, getKeyId, getValueId](jobject jobj) {
    LocalRef<jobject> jkey(ctx->env()->CallObjectMethod(jobj, getKeyId));
    LocalRef<jobject> jvalue(ctx->env()->CallObjectMethod(jobj, getValueId));
    cb(jkey.get(), jvalue.get());
  });
}

}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
