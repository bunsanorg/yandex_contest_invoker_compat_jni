#pragma once

#include <yandex/contest/invoker/compat/Error.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {

struct Error : virtual compat::Error {};

struct JavaError : virtual Error {};

}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
