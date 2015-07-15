#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {

void BaseCxxClass::assignCxx(const char *const ptrName) {
  const Context::Handle ctx = Context::getContext();
  defCtorId_ = ctx->env()->GetMethodID(clazz(), "<init>", "()V");
  ptrId_ = ctx->env()->GetFieldID(clazz(), ptrName, "J");
}

}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
