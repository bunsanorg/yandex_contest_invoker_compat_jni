#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/invoker/Process.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace pipe {

LocalRef<jobject> create(const Pipe &pipe);

}  // namespace pipe
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
