#include "com_yandex_contest_invoker_impl_filesystem_Directory.h"

#include <yandex/contest/invoker/compat/jni/impl/filesystem/Directory.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>

using namespace yandex::contest::invoker::compat::jni;
namespace filesystem = yandex::contest::invoker::filesystem;

namespace {
CxxClass<filesystem::Directory> directoryClass_;
}  // namespace

void Java_com_yandex_contest_invoker_impl_filesystem_Directory_classInit(
    JNIEnv *env, jclass directoryClass) {
  YANDEX_JNI_METHOD_BEGIN(env)
  directoryClass_.assign(directoryClass, "impl");
  YANDEX_JNI_METHOD_END_VOID(env)
}

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace filesystem {
namespace directory {
LocalRef<jobject> create(const invoker::filesystem::Directory &directory) {
  return directoryClass_.setPointerCreate(directory);
}
}  // namespace directory
}  // namespace filesystem
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
