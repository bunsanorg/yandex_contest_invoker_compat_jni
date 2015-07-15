#pragma once

#include <yandex/contest/invoker/compat/jni/JClass.hpp>
#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <utility>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {

class BaseCxxClass : public GlobalJClass {
 public:
  template <typename... Args>
  explicit BaseCxxClass(Args &&... args) {
    assign(std::forward<Args>(args)...);
  }

  BaseCxxClass() = default;

  template <typename C, typename P>
  void assign(const C &clazz, const P &ptr) {
    GlobalJClass::assign(clazz);
    assignCxx(ptr);
  }

 protected:
  LocalRef<jobject> createDefault() const { return newObject(defCtorId_); }

 protected:
  template <typename T>
  void setPointerRaw(jobject self, T *const ptr) const {
    const Context::Handle ctx = Context::getContext();
    ctx->env()->SetLongField(self, ptrId_, ptrToJlong(ptr));
    ctx->throwIfOccured();
  }

  void setPointerRaw(jobject self, std::nullptr_t) const {
    setPointerRaw(self, static_cast<void *>(nullptr));
  }

  template <typename T>
  T *getPointerRaw(jobject self) const {
    BOOST_ASSERT(ptrId_);
    const Context::Handle ctx = Context::getContext();
    jlong ptrLong = ctx->env()->GetLongField(self, ptrId_);
    ctx->throwIfOccured();
    return jlongToPtr<T>(ptrLong);
  }

 private:
  template <typename T>
  static T *jlongToPtr(jlong ptrLong) {
    static_assert(sizeof(ptrLong) >= sizeof(T *), "Insufficient integer size.");
    return reinterpret_cast<T *>(ptrLong);
  }

  template <typename T>
  static jlong ptrToJlong(T *ptr) {
    static_assert(sizeof(jlong) >= sizeof(T *), "Insufficient integer size.");
    return reinterpret_cast<jlong>(ptr);
  }

 private:
  void assignCxx(const char *const ptrName);

 private:
  jmethodID defCtorId_;
  jfieldID ptrId_;
};

template <typename T>
class CxxClass : public BaseCxxClass {
 public:
  using Type = T;

 public:
  using BaseCxxClass::BaseCxxClass;

  CxxClass() = default;

  void setPointer(jobject self, std::unique_ptr<T> &&ptr) const {
    setPointerRaw(self, ptr.get());
    ptr.release();
  }

  T *getPointer(jobject self) const { return getPointerRaw<T>(self); }

  std::unique_ptr<T> releasePointer(jobject self) const {
    std::unique_ptr<T> ptr(getPointerRaw<T>(self));
    setPointer(self, std::unique_ptr<T>());
    return ptr;
  }

  void setReference(jobject self, T &obj) const { setPointerRaw(self, &obj); }

  T &getReference(jobject self) const {
    T *const ptr = getPointerRaw<T>(self);
    BOOST_ASSERT(ptr);
    return *ptr;
  }

  void clearReference(jobject self) const { setPointerRaw(self, nullptr); }

  LocalRef<jobject> setReferenceCreate(T &obj) const {
    LocalRef<jobject> ref(createDefault());
    setReference(ref.get(), obj);
    return ref;
  }

  void finalize(jobject self) const { releasePointer(self); }

  void copyToPointer(jobject self, const T &obj) const {
    std::unique_ptr<T> ptr(new T(obj));
    setPointer(self, std::move(ptr));
  }

  LocalRef<jobject> setPointerCreate(const T &obj) const {
    LocalRef<jobject> ref(createDefault());
    copyToPointer(ref.get(), obj);
    return ref;
  }
};

}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
