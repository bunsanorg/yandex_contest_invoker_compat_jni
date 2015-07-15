#pragma once

#include <jni.h>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

#include <memory>
#include <utility>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {

class Context : private boost::noncopyable {
 public:
  class Handle {
   public:
    Handle(const Handle &);
    Handle &operator=(const Handle &);
    ~Handle();

    Context *operator->() const;

   private:
    friend class Context;

    Handle();
    std::size_t count() const noexcept;
    void assign(std::unique_ptr<Context> &&context) noexcept;
  };

 public:
  /*!
   * \warning Should never be called after JavaVM termination start
   * without JNIEnv argument.
   */
  template <typename... Args>
  static Handle getContext(Args &&... args) {
    Handle handle;
    if (handle.count() == 1) {
      std::unique_ptr<Context> ctx(new Context(std::forward<Args>(args)...));
      handle.assign(std::move(ctx));
    }
    return handle;
  }

  /// \note It is always safe to call it.
  static boost::optional<Handle> getContextOptional();

  /// Should be called before JavaVM termination start.
  static void unregisterGlobalJVM() noexcept;

  static void registerGlobalJVM(JavaVM *jvm);

  static void registerGlobalJVM(JNIEnv *env);

 public:
  ~Context();

  JavaVM *jvm() noexcept;

  /*!
   * \throw JavaError if Java exception has occurred.
   */
  JNIEnv *env();

  JNIEnv *envNoExcept() noexcept;

  /// Throw JavaError if exception occurred.
  void throwIfOccured();

  void throwNew(const char *className, const char *message);

 public:
  static void throwNewFromEnv(JNIEnv *env, const char *className,
                              const char *message) noexcept;

 private:
  /// Context is created from Java call.
  explicit Context(JNIEnv *env);

  /*!
   * \brief Context is created from C++ will be attached to current thread.
   *
   * \note It requires preceding call to registerGlobalJVM()
   * or Context creation with Context(JNIEnv *).
   */
  Context();

  /// Context is created from C++ using specified JavaVM
  /// will be attached to current thread.
  explicit Context(JavaVM *jvm);

 private:
  static JavaVM *getGlobalJVM();

 private:
  JavaVM *jvm_;
  JNIEnv *env_;
  bool detach_;
};

}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
