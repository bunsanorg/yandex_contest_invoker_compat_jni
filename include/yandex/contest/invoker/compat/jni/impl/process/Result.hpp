#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/invoker/Process.hpp>
#include <yandex/contest/invoker/process/Result.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace impl {
namespace process {
namespace result {

LocalRef<jobject> create(const Process::Result &result);

}  // namespace result
}  // namespace process
}  // namespace impl
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
