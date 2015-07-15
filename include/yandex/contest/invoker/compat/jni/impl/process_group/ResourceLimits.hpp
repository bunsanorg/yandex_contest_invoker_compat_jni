#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/invoker/process_group/ResourceLimits.hpp>
#include <yandex/contest/invoker/ProcessGroup.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace process_group {
namespace resource_limits {

LocalRef<jobject> create(const ProcessGroup::ResourceLimits &resourceLimits);

}  // namespace resource_limits
}  // namespace process_group
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
