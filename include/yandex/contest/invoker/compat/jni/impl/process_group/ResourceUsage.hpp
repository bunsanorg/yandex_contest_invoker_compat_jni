#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/invoker/process_group/ResourceUsage.hpp>
#include <yandex/contest/invoker/ProcessGroup.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace process_group {
namespace resource_usage {

LocalRef<jobject> create(const ProcessGroup::ResourceUsage &resourceUsage);

}  // namespace resource_usage
}  // namespace process_group
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
