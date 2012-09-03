#pragma once

#include "yandex/contest/invoker/compat/Error.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni
{
    struct Error: virtual compat::Error {};

    struct JavaError: virtual Error {};
}}}}}
