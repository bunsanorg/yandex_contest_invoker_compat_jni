#include "com_yandex_contest_invoker_impl_filesystem_SymLink.h"

#include <yandex/contest/invoker/compat/jni/impl/filesystem/SymLink.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>

using namespace yandex::contest::invoker::compat::jni;
namespace filesystem = yandex::contest::invoker::filesystem;

namespace {
CxxClass<filesystem::SymLink> symLinkClass_;
}  // namespace

void Java_com_yandex_contest_invoker_impl_filesystem_SymLink_classInit(
    JNIEnv *env, jclass symLinkClass) {
  YANDEX_JNI_METHOD_BEGIN(env)
  symLinkClass_.assign(symLinkClass, "impl");
  YANDEX_JNI_METHOD_END_VOID(env)
}

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace filesystem {
namespace sym_link {
LocalRef<jobject> create(const invoker::filesystem::SymLink &symLink) {
  return symLinkClass_.setPointerCreate(symLink);
}
}  // namespace sym_link
}  // namespace filesystem
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex

jstring Java_com_yandex_contest_invoker_impl_filesystem_SymLink_getValue(
    JNIEnv *env, jobject self) {
  YANDEX_JNI_METHOD_BEGIN_THIS(env, symLinkClass_, self)
  return newStringUTF(this_->value.string()).release();
  YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}
