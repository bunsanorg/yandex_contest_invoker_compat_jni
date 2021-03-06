#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/invoker/filesystem/RegularFile.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace filesystem {
namespace regular_file {

LocalRef<jobject> create(const invoker::filesystem::RegularFile &regularFile);

}  // namespace regular_file
}  // namespace filesystem
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
