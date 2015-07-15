#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/invoker/lxc/RootfsConfig.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace lxc {
namespace rootfs_config {

LocalRef<jobject> create(const invoker::lxc::RootfsConfig &config);

}  // namespace rootfs_config
}  // namespace lxc
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
