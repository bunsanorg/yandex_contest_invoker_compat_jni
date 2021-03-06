#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/invoker/Process.hpp>
#include <yandex/contest/invoker/process/ResourceUsage.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace process {
namespace resource_usage {

LocalRef<jobject> create(const Process::ResourceUsage &resourceUsage);

}  // namespace resource_usage
}  // namespace process
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
