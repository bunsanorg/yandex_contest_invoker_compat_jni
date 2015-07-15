#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/invoker/Process.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace file {

LocalRef<jobject> create(const File &file);

}  // namespace file
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
