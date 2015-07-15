#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/invoker/filesystem/Directory.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace filesystem {
namespace directory {

LocalRef<jobject> create(const invoker::filesystem::Directory &directory);

}  // namespace directory
}  // namespace filesystem
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
