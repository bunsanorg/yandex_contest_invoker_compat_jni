#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/invoker/ContainerConfig.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace container_config {

LocalRef<jobject> create(const ContainerConfig &config);

}  // namespace container_config
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
