#pragma once

#include <yandex/contest/invoker/compat/jni/Context.hpp>

#include <boost/swap.hpp>

#include <utility>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {

template <typename Ptr>
class GlobalRef;

template <typename T>
class GlobalRef<T *> {
 public:
  GlobalRef() : ref_(nullptr) {}

  explicit GlobalRef(T *obj)
      : ref_(
            static_cast<T *>(Context::getContext()->env()->NewGlobalRef(obj))) {
  }

  ~GlobalRef() {
    if (ref_) {
      const boost::optional<Context::Handle> ctx =
          Context::getContextOptional();
      if (ctx) ctx.get()->envNoExcept()->DeleteGlobalRef(ref_);
    }
  }

  GlobalRef(GlobalRef<T *> &&ref) noexcept : GlobalRef() { swap(ref); }

  GlobalRef<T *> &operator=(GlobalRef<T *> &&ref) noexcept {
    swap(ref);
    ref.reset();
  }

  GlobalRef(const GlobalRef<T *> &) = delete;
  GlobalRef<T *> &operator=(const GlobalRef<T *> &) = delete;

  void reset(T *obj = nullptr) {
    GlobalRef<T *> ref(obj);
    swap(ref);
  }

  T *get() const noexcept { return ref_; }

  explicit operator bool() const noexcept { return ref_; }

  void swap(GlobalRef<T *> &ref) noexcept {
    using boost::swap;
    swap(ref_, ref.ref_);
  }

 private:
  T *ref_;
};

template <typename Ptr>
inline void swap(GlobalRef<Ptr> &a, GlobalRef<Ptr> &b) noexcept {
  a.swap(b);
}

}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
