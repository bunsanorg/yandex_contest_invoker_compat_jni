#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/system/unistd/access/Id.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace unistd {
namespace access {
namespace id {

LocalRef<jobject> create(const system::unistd::access::Id &id);

}  // namespace id
}  // namespace access
}  // namespace unistd
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
