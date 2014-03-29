#pragma once

#include <yandex/contest/invoker/compat/jni/Error.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace config
{
    struct Error: virtual jni::Error {};

    struct VariantError: virtual Error {};

    struct VariantNoTypesLeftError: virtual VariantError {};

    struct VariantTypeHasNotTypeInfoError: virtual VariantError {};
}}}}}}
